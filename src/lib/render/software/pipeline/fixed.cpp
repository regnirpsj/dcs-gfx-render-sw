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
          TRACE_ALWAYS("hugh::render::software::pipeline::fixed::process");

          using vertex_list_type = primitive::base::vertex_list_type;

          vertex_list_type vertices;
          
          for (auto const& v : p.vertices) {
            vertex
              tmp(clip_to_ndc(eye_to_clip(world_to_eye(object_to_world(glm::vec4(v.position, 1))))),
                  v.attributes);
            
            vertices.push_back(tmp);

            ++count_.vertices.processed;
          }

          using fragment_list_type = rasterizer::base::fragment_list_type;

          fragment_list_type fragments;
          
          switch (p.topology) {
          case primitive::topology::point_list:
            {
              if (p.indices.empty()) {
                for (auto const& v : p.vertices) {
                  fragment_list_type const fl((*rasterizer)->process(v));

                  fragments.insert(fragments.end(), fl.begin(), fl.end());

                  count_.fragments.created += fl.size();
                }
              } else {
                for (auto const& i : p.indices) {
                  fragment_list_type const fl((*rasterizer)->process(vertices[i]));

                  fragments.insert(fragments.end(), fl.begin(), fl.end());

                  count_.fragments.created += fl.size();
                }
              }
            }
            break;

          case primitive::topology::line_list:
            {
              if (p.indices.empty()) {
                for (unsigned i(0); i < p.vertices.size(); i += 2) {
                  fragment_list_type const
                    fl((*rasterizer)->process(line(vertices[i+0],
                                                   vertices[i+1])));
                  
                  fragments.insert(fragments.end(), fl.begin(), fl.end());
                  
                  count_.fragments.created += fl.size();
                }
              } else {
                for (unsigned i(0); i < p.indices.size(); i += 2) {
                  fragment_list_type const
                    fl((*rasterizer)->process(line(vertices[p.indices[i+0]],
                                                   vertices[p.indices[i+1]])));
                  
                  fragments.insert(fragments.end(), fl.begin(), fl.end());
                  
                  count_.fragments.created += fl.size();
                }
              }
            }
            break;

          case primitive::topology::line_strip:
            {
              if (p.indices.empty()) {
                for (unsigned i(0); i < p.vertices.size()-1; ++i) {
                  fragment_list_type const
                    fl((*rasterizer)->process(line(vertices[i+0],
                                                   vertices[i+1])));
                  
                  fragments.insert(fragments.end(), fl.begin(), fl.end());
                  
                  count_.fragments.created += fl.size();
                }
              } else {
                for (unsigned i(0); i < p.indices.size()-1; ++i) {
                  fragment_list_type const
                    fl((*rasterizer)->process(line(vertices[p.indices[i+0]],
                                                   vertices[p.indices[i+1]])));
                  
                  fragments.insert(fragments.end(), fl.begin(), fl.end());
                  
                  count_.fragments.created += fl.size();
                }
              }
            }
            break;
            
          case primitive::topology::triangle_list:
            {
              if (p.indices.empty()) {
                for (unsigned i(0); i < p.vertices.size(); i += 3) {
                  fragment_list_type const
                    fl((*rasterizer)->process(triangle(vertices[i+0],
                                                       vertices[i+1],
                                                       vertices[i+2])));

                  fragments.insert(fragments.end(), fl.begin(), fl.end());

                  count_.fragments.created += fl.size();
                }
              } else {
                for (unsigned i(0); i < p.indices.size(); i += 3) {
                  fragment_list_type const
                    fl((*rasterizer)->process(triangle(vertices[p.indices[i+0]],
                                                       vertices[p.indices[i+1]],
                                                       vertices[p.indices[i+2]])));

                  fragments.insert(fragments.end(), fl.begin(), fl.end());

                  count_.fragments.created += fl.size();
                }
              }
            }
            break;

          case primitive::topology::triangle_strip:
            {
              if (p.indices.empty()) {
                for (unsigned i(0); i < p.vertices.size()-2; ++i) {
                  fragment_list_type const
                    fl((*rasterizer)->process(triangle(vertices[i+0],
                                                       vertices[i+1],
                                                       vertices[i+2])));
                  
                  fragments.insert(fragments.end(), fl.begin(), fl.end());
                  
                  count_.fragments.created += fl.size();
                }
              } else {
                for (unsigned i(0); i < p.indices.size()-2; ++i) {
                  fragment_list_type const
                    fl((*rasterizer)->process(triangle(vertices[p.indices[i+0]],
                                                       vertices[p.indices[i+1]],
                                                       vertices[p.indices[i+2]])));
                  
                  fragments.insert(fragments.end(), fl.begin(), fl.end());
                  
                  count_.fragments.created += fl.size();
                }
              }
            }
            break;
            
          default:
            {
              std::ostringstream ostr;

              ostr << "<hugh::render::software::pipeline::fixed::process>: "
                   << "unrecognized primitive topology (" << unsigned(p.topology) << ")";
              
              throw std::logic_error(ostr.str());
            }
            break;
          }

          for (auto const& f : fragments) {
            if ((*depthbuffer)->update(f)) {
              (*colorbuffer)->update(f);

              ++count_.fragments.updated;
            }
          }

#if 0
          {
            std::cout << support::trace::prefix()
              // << "hugh::render::software::pipeline::fixed::process: "
                      << p.topology << '\t'
                      << "v:"
                      << count_.vertices.processed
                      << " -> f:"
                      << count_.fragments.created
                      << " -> p:"
                      << count_.fragments.updated
                      << '\n';
          }
#endif
        }
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
