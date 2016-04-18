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

          attribute::list attr (f.attributes);
          auto            found(attr.find(attribute::type::color));
          
          if (attr.end() == found) {
            attr[attribute::type::color] = glm::vec4(1, 1, 1, 0);
          }
          
          return fragment(f.position, f.depth, attr);
        }
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
