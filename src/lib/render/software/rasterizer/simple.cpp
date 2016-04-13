// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/rasterizer/simple.cpp                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/rasterizer/simple.hpp"

// includes, system

#include <glm/gtx/intersect.hpp> // glm::intersectRayTriangle
#include <glm/gtx/io.hpp>        // glm::operator<<

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

      namespace rasterizer {
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        simple::simple(viewport_type const& a)
          : base(a)
        {
          TRACE("hugh::render::software::rasterizer::simple::simple");
        }
      
        /* virtual */
        simple::~simple()
        {
          TRACE("hugh::render::software::rasterizer::simple::~simple");
        }
      
        /* virtual */ simple::fragment_list_type
        simple::process(line const& l) const
        {
          TRACE("hugh::render::software::rasterizer::simple::process(line)");

          // std::cout << "l.p0:" << l.p0 << ", l.p1:" << l.p1 << std::endl;
    
          glm::ivec2 p0   (glm::min(glm::max(glm::ivec2(l.p0.position.x, l.p0.position.y),
                                             glm::ivec2(viewport->x, viewport->y)),
                                    glm::ivec2(viewport->width, viewport->height)));
          glm::ivec2 p1   (glm::min(glm::max(glm::ivec2(l.p1.position.x, l.p1.position.y),
                                             glm::ivec2(viewport->x, viewport->y)),
                                    glm::ivec2(viewport->width, viewport->height)));
          bool       steep(false);

          // std::cout << "  p0:" << p0 << ",   p1:" << p1 << std::endl;
    
          if (std::abs(p0.x - p1.x) < std::abs(p0.y - p1.y)) {
            using std::swap;
            
            swap(p0.x, p0.y);
            swap(p1.x, p1.y);
      
            steep = true;
          }
    
          if (p0.x > p1.x) {
            using std::swap;
            
            swap(p0.x, p1.x);
            swap(p0.y, p1.y);
          }
    
          fragment_list_type result;

          glm::vec3 const ldir (l.p1.position - l.p0.position);
          glm::vec2 const delta(p1.x - p0.x, p1.y - p0.y);
          signed          derr2(2.0 * std::abs(delta.y));
          signed          err2 (0.0);
          signed          y    (p0.y);

          for (signed x(p0.x); x <= p1.x; ++x) {      
            if (steep) {      
              float const depth(glm::length(glm::cross(l.p0.position - glm::vec3(y, x, 0), ldir)) /
                                glm::length(ldir));

              result.push_back(fragment(glm::uvec2(y, x), depth));
            } else {
              float const depth(glm::length(glm::cross(l.p0.position - glm::vec3(x, y, 0), ldir)) /
                                glm::length(ldir));

              result.push_back(fragment(glm::uvec2(x, y), depth));
            }
      
            err2 += derr2;

            if (delta.x < err2) {
              y    += (0 < delta.y) ? 1 : -1;
              err2 -= 2.0 * delta.x;
            }
          }
    
          return result;
        }
      
        /* virtual */ simple::fragment_list_type
        simple::process(triangle const& t) const
        {
          TRACE("hugh::render::software::rasterizer::simple::process(triangle)");

          fragment_list_type result;
          float const        area2(((t.p1.position.x - t.p0.position.x) *
                                    (t.p2.position.y - t.p0.position.y)) -
                                   ((t.p2.position.x - t.p0.position.x) *
                                    (t.p1.position.y - t.p0.position.y)));

          if (0.0 < area2) {
            std::array<glm::ivec2 const, 2> const bbox = {
              {
                glm::max(glm::ivec2(viewport->x, viewport->y),
                         glm::min(glm::ivec2(viewport->width, viewport->height),
                                  glm::min(glm::ivec2(t.p0.position.x, t.p0.position.y),
                                           glm::min(glm::ivec2(t.p1.position.x, t.p1.position.y),
                                                    glm::ivec2(t.p2.position.x, t.p2.position.y))))),
                glm::max(glm::ivec2(viewport->x, viewport->y),
                         glm::min(glm::ivec2(viewport->width, viewport->height),
                                  glm::max(glm::ivec2(t.p0.position.x, t.p0.position.y),
                                           glm::max(glm::ivec2(t.p1.position.x, t.p1.position.y),
                                                    glm::ivec2(t.p2.position.x, t.p2.position.y))))),
              }
            };

            // std::cout << t << " -> [" << bbox[0] << ':' << bbox[1] << ']' << std::endl;

            glm::ivec2 p;

            for (p.y = bbox[0].y; p.y <= bbox[1].y; ++p.y) {
              for (p.x = bbox[0].x; p.x <= bbox[1].x; ++p.x) {
                glm::vec3  bary;
                bool const hit(glm::intersectRayTriangle(glm::vec3(p, 0),  // ray origin
                                                         glm::vec3(0,0,1), // ray direction
                                                         t.p0.position,    // [
                                                         t.p1.position,    // triangle
                                                         t.p2.position,    // ]
                                                         bary));           // barycentric hit

                if (hit) {
                  bary /= area2;
          
                  float const depth(                             t.p0.position.z   +
                                    (bary.y * (t.p1.position.z - t.p0.position.z)) +
                                    (bary.z * (t.p2.position.z - t.p0.position.z)));

                  // std::cout << area2 << ':' << p << ':' << bary << ':' << depth << std::endl;
          
                  result.push_back(fragment(glm::uvec2(p.x, p.y), depth));
                }
              }
            }
          }
    
          return result;
        }

      } // namespace rasterizer {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
