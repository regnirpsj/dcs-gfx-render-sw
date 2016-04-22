// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/fixed/base.cpp                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/pipeline/fixed/base.hpp"

// includes, system

#include <glm/gtc/constants.hpp> // glm::pi<>
#include <sstream>               // std::ostringstream
#include <stdexcept>             // std::logic_error

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal
  
} // namespace {

namespace hugh {

  namespace render {

    namespace software {

      namespace pipeline {

        namespace fixed {
          
          // variables, exported
  
          // functions, exported

          /* explicit */
          base::base()
            : pipeline::base()
          {
            TRACE("hugh::render::software::pipeline::fixed::base::base");
          }
        
          /* virtual */
          base::~base()
          {
            TRACE("hugh::render::software::pipeline::fixed::base::~base");
          }

          /* virtual */ void
          base::process(primitive::base const& p)
          {
            TRACE("hugh::render::software::pipeline::fixed::base::process(" +
                  std::to_string(unsigned(p.topology)) + ")");

            using topology = primitive::topology;
          
            statistics       lstats;
            vertex_list_type vertices;

            vertices.reserve(p.vertices.size());
          
            for (auto const& v : p.vertices) {
              vertices.push_back(transform(v));
            }

            lstats.vertices.transformed += vertices.size();

            fragment_list_type fragments;
          
            switch (p.topology) {
            case topology::point_list:
              fragments = raster<topology::point_list>    (p.indices, vertices); break;
            
            case topology::line_list:
              fragments = raster<topology::line_list>     (p.indices, vertices); break;
            
            case topology::line_strip:
              fragments = raster<topology::line_strip>    (p.indices, vertices); break;
            
            case topology::triangle_list:
              fragments = raster<topology::triangle_list> (p.indices, vertices); break;
            
            case topology::triangle_strip:
              fragments = raster<topology::triangle_strip>(p.indices, vertices); break;
            
            default:
              {
                std::ostringstream ostr;
              
                ostr << "<hugh::render::software::pipeline::fixed::base::process>: "
                     << "unrecognized primitive topology (" << unsigned(p.topology) << ")";
              
                throw std::logic_error(ostr.str());
              }
              break;
            }

            lstats.fragments.created += fragments.size();
          
            for (auto const& f : fragments) {
              if (!(*depthbuffer)->zcull(f)) {
                fragment const fs(shade(f));

                ++lstats.fragments.shaded;

                if ((*depthbuffer)->ztest(fs)) {
                  (*colorbuffer)->update(fs);
              
                  ++lstats.fragments.updated;
                } else {
                  ++lstats.fragments.ztestfailed;
                }
              } else {
                ++lstats.fragments.zculled;
              }
            }
          
            const_cast<statistics&>(*stats) += lstats;
          
#if 0
            {
              std::cout << support::trace::prefix()
                // << "hugh::render::software::pipeline::fixed::base::process: "
                        << (p.indices.empty() ? "!" : " ") << "idx "
                        << p.topology
                        << "  \t"
                        << lstats
                        << '\t'
                        << *stats
                        << '\n';
            }
#endif
          }

          vertex
          base::transform(vertex const& v) const
          {
            TRACE("hugh::render::software::pipeline::fixed::base::transform");

            glm::vec4 const homogeneous_coord(v.position, 1);
            glm::vec4 const world_coord      (object_to_world(homogeneous_coord));
            glm::vec4 const eye_coord        (world_to_eye   (world_coord));
            glm::vec4 const clip_coord       (eye_to_clip    (eye_coord));
            glm::vec3 const ndc_coord        (clip_to_ndc    (clip_coord));
            glm::vec3 const window_coord     (ndc_to_window  (ndc_coord));
          
            return vertex(window_coord, v.attributes);
          }

          namespace {

            template <typename T>
            inline T
            saturate(T a)
            {
              return glm::clamp(a, T(0), T(1));
            }
            
            using light_t = hugh::scene::object::light::base::rep;

            struct light_cone_parameter_t {
              
              float cos_inner_angle;
              float cos_outer_angle;
              float diff_inner_outer;
              bool  compute_falloff_spot;

              explicit light_cone_parameter_t(light_t const& l)
                : cos_inner_angle     (0.0f),
                  cos_outer_angle     (0.0f),
                  diff_inner_outer    (0.0f),
                  compute_falloff_spot((0.0f != l.position.w) && (glm::pi<float>() != l.cutoff))
              {
                if (compute_falloff_spot) {
                  float const cos_cutoff(std::cos(l.cutoff));

                  cos_outer_angle = saturate(cos_cutoff);

                  // inner = (1 - (spotExp / 128)) * outer
                  cos_inner_angle  = saturate(cos((1.0f - (l.exponent / 128.0f)) * cos_cutoff));
                  diff_inner_outer = (cos_inner_angle - cos_outer_angle);
                }
              }
              
            };

            glm::vec3
            light_vector(light_t const& l, glm::vec3 const& P)
            {
              glm::vec4 result(l.position); // assume directional: lvec = lpos

              if (0.0f != result.w) {
                result.xyz() -= P;          // no it's positional: lvec = lpos - opos
              }

              return result.xyz();
            }

            float
            light_attenuation(light_t const& l, float d)
            {
              float const attenuation_at_lpos_infty(1.0f);

              return ((0.0f != l.position.w)
                      ? 1.0f / ((l.attenuation.x        ) +
                                (l.attenuation.y * d    ) +
                                (l.attenuation.z * d * d))
                      : attenuation_at_lpos_infty);
            }

            glm::vec4
            lit(float NdotL, float NdotH, float exponent)
            {
              float const ambient (1.0f);
              float const diffuse (NdotL);
              float const specular((0.0f > std::min(NdotL, NdotH))
                                   ? 0.0f
                                   : std::pow(NdotH, exponent));
              
              return glm::vec4(ambient, diffuse, specular, 1.0f);
            }
            
          }
          
          fragment
          base::shade(fragment const& f) const
          {
            TRACE("hugh::render::software::pipeline::fixed::base::shade");

            attribute::list attr(f.attributes);

            if (nullptr != *material) {              
              glm::vec3 const P;
              glm::vec3 const N;
              glm::mat4 const C;
            
              glm::vec3 laccum_ambient (0,0,0);
              glm::vec3 laccum_diffuse (0,0,0);
              glm::vec3 laccum_specular(0,0,0);
            
              for (auto const& l : *lights) {
                if (l.active) {
                  glm::vec3 L          (light_vector     (l, P));
                  float     attenuation(light_attenuation(l, glm::length(L)));

                  L = glm::normalize(L);
                
                  float const NdotL(std::max(glm::dot(N, L), 0.0f));
                
                  if (0.0 < NdotL) {
                    light_cone_parameter_t lcp(l);

                    if (lcp.compute_falloff_spot) {
                      float const cos_cur_angle(glm::dot(-L, normalize(l.direction)));

                      // avoids dynamic branching
                      attenuation *= saturate((cos_cur_angle - lcp.cos_outer_angle) /
                                              lcp.diff_inner_outer);
                    }
      
                    float const     exponent  (glm::clamp((*material)->shininess, 0.0f, 128.0f));
                    glm::vec3 const V         (C[3].xyz() - P);
                    glm::vec3 const H         (L + V);
                    // float const     NdotV     (std::max(glm::dot(N, V), 0.0f));
                    float const     NdotH     (std::max(glm::dot(N, H), 0.0f));
                    glm::vec4 const lit_result(lit(NdotL, NdotH, exponent));
                  
                    laccum_diffuse  += (attenuation * l.diffuse  * lit_result.y);
                    laccum_specular += (attenuation * l.specular * lit_result.z);
                  }
                
                  laccum_ambient += attenuation * l.ambient;
                }
              }
            
              glm::vec4 result((*material)->emission, (*material)->alpha);
            
              result.rgb() += laccum_ambient  * (*material)->ambient;
              result.rgb() += laccum_diffuse  * (*material)->diffuse;
              result.rgb() += laccum_specular * (*material)->specular;
            
              attr[attribute::type::color] = result;
            } else {
              auto found(attr.find(attribute::type::color));
          
              if (attr.end() == found) {
                attr[attribute::type::color] = glm::vec4(1, 1, 1, 0);
              }
            }
          
            return fragment(f.position, f.depth, attr);
          }

        } // namespace fixed {
      
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
