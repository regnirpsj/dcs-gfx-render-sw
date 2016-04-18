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

#include <array>                 // std::array<>
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

  namespace attribute = hugh::render::software::attribute;
  
  // variables, internal

  std::array<attribute::type const, 5> const attribute_types = {
    {
      attribute::type::position,
      attribute::type::normal,
      attribute::type::color,
      attribute::type::texcoord,
      attribute::type::bitangent,
    }
  };

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
        simple::process(vertex const& v) const
        {
          TRACE("hugh::render::software::rasterizer::simple::process(vertex)");
          
          fragment_list_type result;

          if (viewport_.contains(glm::vec3(v.position.xy(), 0))) {
            result.push_back(fragment(glm::uvec2(v.position.x, v.position.y),
                                      v.position.z,
                                      v.attributes));
          }
          
          return result;
        }

        /* virtual */ simple::fragment_list_type
        simple::process(vertex const& v0, vertex const& v1) const
        {
          TRACE("hugh::render::software::rasterizer::simple::process(line)");

          // std::cout << "v0:" << v0 << ", v1:" << v1 << std::endl;

          fragment_list_type result;
          
          if (viewport_.contains(glm::vec3(v0.position.xy(), 0)) ||
              viewport_.contains(glm::vec3(v1.position.xy(), 0))) {
            std::vector<std::pair<attribute::type, std::array<glm::vec4, 2>>> base_attributes;

            if (!v0.attributes.empty() ||
                !v1.attributes.empty()) {
              for (auto a : attribute_types) {
                auto const               p0found(v0.attributes.find(a));
                auto const               p1found(v1.attributes.find(a));
                std::array<glm::vec4, 2> tmp = { glm::vec4(0), glm::vec4(0), };
                bool                     insert(false);
              
                if (v0.attributes.end() != p0found) {
                  tmp[0] = p0found->second;
                  insert = true;
                }
              
                if (v1.attributes.end() != p1found) {
                  tmp[1] = p1found->second;
                  insert = true;
                }

                if (insert) {
                  base_attributes.push_back({ a, tmp });
                }
              }
            }
            
            std::array<glm::ivec2, 2> line = {
              {
                glm::min(glm::max(glm::ivec2(v0.position.x, v0.position.y),
                                  glm::ivec2(viewport_.x, viewport_.y)),
                         glm::ivec2(viewport_.width, viewport_.height)),
                glm::min(glm::max(glm::ivec2(v1.position.x, v1.position.y),
                                  glm::ivec2(viewport_.x, viewport_.y)),
                         glm::ivec2(viewport_.width, viewport_.height))
              }
            };

            bool steep(false);

            // std::cout << "  line[0]:" << line[0] << ",   line[1]:" << line[1] << std::endl;
    
            if (std::abs(line[0].x - line[1].x) < std::abs(line[0].y - line[1].y)) {
              using std::swap;
            
              swap(line[0].x, line[0].y);
              swap(line[1].x, line[1].y);
      
              steep = true;
            }
    
            if (line[0].x > line[1].x) {
              using std::swap;
            
              swap(line[0].x, line[1].x);
              swap(line[0].y, line[1].y);
            }

            glm::vec3 const ldir (v1.position - v0.position);
            glm::vec2 const delta(line[1].x - line[0].x, line[1].y - line[0].y);
            signed          derr2(2.0 * std::abs(delta.y));
            signed          err2 (0.0);
            signed          y    (line[0].y);

            for (signed x(line[0].x); x <= line[1].x; ++x) {
              attribute::list attributes;

              if (!base_attributes.empty()) {
                float const weight(glm::length(glm::vec2(x-line[0].x, y-line[0].y)) /
                                   glm::length(delta));
              
                for (auto a : base_attributes) {
                  attributes[a.first] = (weight * a.second[0]) + ((1-weight) * a.second[1]);
                }
              }
              
              if (steep) {      
                float const depth(glm::length(glm::cross(v0.position - glm::vec3(y, x, 0),
                                                         ldir)) / glm::length(ldir));

                result.push_back(fragment(glm::uvec2(y, x), depth, attributes));
              } else {
                float const depth(glm::length(glm::cross(v0.position - glm::vec3(x, y, 0),
                                                         ldir)) / glm::length(ldir));

                result.push_back(fragment(glm::uvec2(x, y), depth, attributes));
              }
      
              err2 += derr2;

              if (delta.x < err2) {
                y    += (0 < delta.y) ? 1 : -1;
                err2 -= 2.0 * delta.x;
              }
            }
          }
          
          return result;
        }
      
        /* virtual */ simple::fragment_list_type
        simple::process(vertex const& v0, vertex const& v1, vertex const& v2) const
        {
          TRACE("hugh::render::software::rasterizer::simple::process(triangle)");

          fragment_list_type result;
          float const        area2(((v1.position.x - v0.position.x) *
                                    (v2.position.y - v0.position.y)) -
                                   ((v2.position.x - v0.position.x) *
                                    (v1.position.y - v0.position.y)));

          if ((0.0 < area2) &&
              (viewport_.contains(glm::vec3(v0.position.xy(), 0)) ||
               viewport_.contains(glm::vec3(v1.position.xy(), 0)) ||
               viewport_.contains(glm::vec3(v2.position.xy(), 0)))) {
            std::vector<std::pair<attribute::type, std::array<glm::vec4, 3>>> base_attributes;

            if (!v0.attributes.empty() ||
                !v1.attributes.empty() ||
                !v2.attributes.empty()) {
              for (auto a : attribute_types) {
                auto const               p0found(v0.attributes.find(a));
                auto const               p1found(v1.attributes.find(a));
                auto const               p2found(v2.attributes.find(a));
                std::array<glm::vec4, 3> tmp = { glm::vec4(0), glm::vec4(0), glm::vec4(0), };
                bool                     insert(false);
              
                if (v0.attributes.end() != p0found) {
                  tmp[0] = p0found->second;
                  insert = true;
                }
              
                if (v1.attributes.end() != p1found) {
                  tmp[1] = p1found->second;
                  insert = true;
                }
              
                if (v2.attributes.end() != p1found) {
                  tmp[2] = p2found->second;
                  insert = true;
                }

                if (insert) {
                  base_attributes.push_back({ a, tmp });
                }
              }
            }
            
            std::array<glm::ivec2 const, 2> const bbox = {
              {
                glm::max(glm::ivec2(viewport_.x, viewport_.y),
                         glm::min(glm::ivec2(viewport_.width, viewport_.height),
                                  glm::min(glm::ivec2(v0.position.x, v0.position.y),
                                           glm::min(glm::ivec2(v1.position.x, v1.position.y),
                                                    glm::ivec2(v2.position.x, v2.position.y))))),
                glm::max(glm::ivec2(viewport_.x, viewport_.y),
                         glm::min(glm::ivec2(viewport_.width, viewport_.height),
                                  glm::max(glm::ivec2(v0.position.x, v0.position.y),
                                           glm::max(glm::ivec2(v1.position.x, v1.position.y),
                                                    glm::ivec2(v2.position.x, v2.position.y))))),
              }
            };

            // std::cout << t << " -> [" << bbox[0] << ':' << bbox[1] << ']' << std::endl;
            
            glm::ivec2 p;

            for (p.y = bbox[0].y; p.y <= bbox[1].y; ++p.y) {
              for (p.x = bbox[0].x; p.x <= bbox[1].x; ++p.x) {
                glm::vec3  bary;
                bool const hit(glm::intersectRayTriangle(glm::vec3(p, 0),  // ray origin
                                                         glm::vec3(0,0,1), // ray direction
                                                         v0.position,    // [
                                                         v1.position,    // triangle
                                                         v2.position,    // ]
                                                         bary));           // barycentric hit

                if (hit) {                  
                  attribute::list attributes;

                  for (auto a : base_attributes) {
                    attributes[a.first] = ((bary.x * a.second[0]) +
                                           (bary.y * a.second[1]) +
                                           (bary.z * a.second[2]));
                  }
                  
                  bary /= area2;
          
                  float const depth(/*                      */ v0.position.z   +
                                    (bary.y * (v1.position.z - v0.position.z)) +
                                    (bary.z * (v2.position.z - v0.position.z)));
                  
                  // std::cout << area2 << ':' << p << ':' << bary << ':' << depth << std::endl;

                  result.push_back(fragment(glm::uvec2(p.x, p.y), depth, attributes));
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
