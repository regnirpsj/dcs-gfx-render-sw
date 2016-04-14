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

//#include <>

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
          TRACE("hugh::render::software::pipeline::fixed::process");

          using vertex_list_type = primitive::base::vertex_list_type;

          vertex_list_type vertices;
          
          for (auto const& v : p.vertices) {
            vertex
              tmp(clip_to_ndc(eye_to_clip(world_to_eye(object_to_world(glm::vec4(v.position, 1))))),
                  v.attributes);
            
            vertices.push_back(tmp);

            ++count_.vertices;
          }

          using fragment_list_type = rasterizer::base::fragment_list_type;

          fragment_list_type fragments;
          
          switch (p.type) {
          case primitive::type::points:
            {
              for (unsigned i(0); i < p.indices.size(); i += 1) {
                fragment_list_type const
                  fl((*rasterizer)->process(vertices[p.indices[i]]));

                fragments.insert(fragments.end(), fl.begin(), fl.end());

                count_.fragments[0] += fl.size();
              }
            }
            break;

          case primitive::type::lines:
            {
              for (unsigned i(0); i < p.indices.size(); i += 2) {
                fragment_list_type const
                  fl((*rasterizer)->process(line(vertices[p.indices[i+0]],
                                                 vertices[p.indices[i+1]])));

                fragments.insert(fragments.end(), fl.begin(), fl.end());

                count_.fragments[0] += fl.size();
              }
            }
            break;

          case primitive::type::triangles:
            {
              for (unsigned i(0); i < p.indices.size(); i += 3) {
                fragment_list_type const
                  fl((*rasterizer)->process(triangle(vertices[p.indices[i+0]],
                                                     vertices[p.indices[i+1]],
                                                     vertices[p.indices[i+2]])));

                fragments.insert(fragments.end(), fl.begin(), fl.end());

                count_.fragments[0] += fl.size();
              }
            }
            break;

          default:
            break;
          }

          for (auto const& f : fragments) {
#if 0
            if (depthbuffer->test(f)) {
              framebuffer->update(f);

              ++count_.fragments[1];
            }
#endif
          }

          std::cout << support::trace::prefix()
                    << "hugh::render::software::pipeline::fixed::process: "
                    << "v: "
                    << count_.vertices
                    << " -> f:"
                    << count_.fragments[0]
                    << " -> p:"
                    << count_.fragments[1]
                    << '\n';
        }

      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
