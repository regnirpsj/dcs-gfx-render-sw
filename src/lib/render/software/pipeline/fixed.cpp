// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/fixed.cpp                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/pipeline/fixed.hpp"

// includes, system

#include <sstream>   // std::ostringstream
#include <stdexcept> // std::logic_error

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
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        fixed::fixed()
          : base()
        {
          TRACE("hugh::render::software::pipeline::fixed::fixed");
        }
        
        /* virtual */
        fixed::~fixed()
        {
          TRACE("hugh::render::software::pipeline::fixed::~fixed");
        }

        /* virtual */ void
        fixed::process(primitive::base const& p)
        {
          TRACE("hugh::render::software::pipeline::fixed::process(" +
                std::to_string(unsigned(p.topology)) + ")");

          using topology = primitive::topology;
          
          statistics       lstats;
          vertex_list_type vertices;

          vertices.reserve(p.vertices.size());
          
          for (auto const& v : p.vertices) {
            vertices.push_back(transform(v));
          }

          lstats.vertices.processed += vertices.size();

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
              
              ostr << "<hugh::render::software::pipeline::fixed::process>: "
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
              }
            }
          }
          
          const_cast<statistics&>(*stats) += lstats;
          
#if 1
          {
            std::cout << support::trace::prefix()
              // << "hugh::render::software::pipeline::fixed::process: "
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
        fixed::transform(vertex const& v) const
        {
          TRACE("hugh::render::software::pipeline::fixed::transform");

          glm::vec4 const vh(v.position, 1);
          
          return vertex(clip_to_ndc(eye_to_clip(world_to_eye(object_to_world(vh)))), v.attributes);
        }
        
        fragment
        fixed::shade(fragment const& f) const
        {
          TRACE("hugh::render::software::pipeline::fixed::shade");

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
                glm::vec3 L;
                float     att(1.0);

                L = glm::normalize(L);
                
                float const NdotL(std::max(glm::dot(N, L), 0.0f));
                
                if (0.0 < NdotL) {
                  float const     exp  (glm::clamp((*material)->shininess, 0.0f, 128.0f));
                  glm::vec3 const V    (C[3].xyz() - P);
                  glm::vec3 const H    (L + V);
                  float const     NdotV(std::max(glm::dot(N, V), 0.0f));
                  float const     NdotH(std::max(glm::dot(N, H), 0.0f));
                  // glm::vec4 const lresult(lit(NdotL, NdotH, exp));
                  
                  // laccum_diffuse  += (att * l.diffuse  * lresult.y);
                  // laccum_specular += (att * l.specular * lresult.z);
                }
                
                laccum_ambient += att * l.ambient;
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
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
