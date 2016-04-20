// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/pipeline_fixed_shared.cpp                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "pipeline_fixed_shared.hpp"

// includes, system

#include <boost/test/unit_test.hpp>

// includes, project

#include <hugh/render/software/pipeline/fixed/base.hpp>
#include <hugh/render/software/primitives.hpp>

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
      
      namespace test {

        // variables, exported

        viewport_type const default_viewport(0, 0, 160, 120, 0, 1);
        
        // functions, exported
        
        void
        process_point_list(pipeline::fixed::base& ppl)
        {
          TRACE("hugh::render::software::test::process_point_list");
          
          using point_list  = primitive::point_list;
          using index_list  = point_list::index_list_type;
          using vertex_list = point_list::vertex_list_type;

          auto const&    vp    (*(*ppl.rasterizer)->viewport);
          unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(200)));
          vertex_list    vl;
    
          for (unsigned x(vp.x); x < (vp.x + vp.width); x += stride) {
            for (unsigned y(vp.y); y < (vp.y + vp.height); y += stride) {
              vl.push_back(vertex(glm::vec3(x, y,  1.5)));  // > vp.far  -> false
              vl.push_back(vertex(glm::vec3(x, y,  0.75))); // < current -> true
              vl.push_back(vertex(glm::vec3(x, y,  0.25))); // < current -> true
              vl.push_back(vertex(glm::vec3(x, y,  0.5)));  // > current -> false
              vl.push_back(vertex(glm::vec3(x, y, -0.25))); // < vp.near -> false
            }
          }
          
          {
            point_list const p(vl);
            
            ppl.process(p);
          }
          
          auto const lstats(*ppl.stats);
          
          {
            index_list il(vl.size());
            
            std::iota(il.begin(), il.end(), 0);
            
            point_list const p(vl, il);
            
            ppl.process(p);
          }
          
          auto const ilstats(*ppl.stats);
          
          BOOST_CHECK(ilstats.vertices.transformed  >  lstats.vertices.transformed);
          BOOST_CHECK(ilstats.fragments.created     >  lstats.fragments.created);
          BOOST_CHECK(ilstats.fragments.zculled     >  lstats.fragments.zculled);
          BOOST_CHECK(ilstats.fragments.shaded      == lstats.fragments.shaded);
          BOOST_CHECK(ilstats.fragments.ztestfailed == lstats.fragments.ztestfailed);
          BOOST_CHECK(ilstats.fragments.updated     == lstats.fragments.updated);
        }
        
        void
        process_line_list(pipeline::fixed::base& ppl)
        {
          TRACE("hugh::render::software::test::process_line_list");
          
          using line_list   = primitive::line_list;
          using index_list  = line_list::index_list_type;
          using vertex_list = line_list::vertex_list_type;

          auto const&    vp    (*(*ppl.rasterizer)->viewport);
          unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(100)));
          vertex_list    vl;
    
          for (unsigned x(vp.x); x < (vp.x + vp.width); x += stride) {
            for (unsigned y(vp.y); y < (vp.y + vp.height); y += stride) {
              vl.push_back(vertex(glm::vec3(       x,        y, 0.25)));
              vl.push_back(vertex(glm::vec3(x+stride, y+stride, 0.75)));
              vl.push_back(vertex(glm::vec3(x+stride, y+stride, 0.25)));
              vl.push_back(vertex(glm::vec3(       x,        y, 0.75)));
            }
          }

          {
            line_list const l(vl);
    
            ppl.process(l);
          }

          auto const lstats(*ppl.stats);
    
          {
            index_list il(vl.size());

            std::iota(il.begin(), il.end(), 0);
      
            line_list const l(vl, il);
    
            ppl.process(l);
          }
    
          auto const ilstats(*ppl.stats);

          BOOST_CHECK(ilstats.vertices.transformed  >  lstats.vertices.transformed);
          BOOST_CHECK(ilstats.fragments.created     >  lstats.fragments.created);
          BOOST_CHECK(ilstats.fragments.zculled     >  lstats.fragments.zculled);
          BOOST_CHECK(ilstats.fragments.shaded      == lstats.fragments.shaded);
          BOOST_CHECK(ilstats.fragments.ztestfailed == lstats.fragments.ztestfailed);
          BOOST_CHECK(ilstats.fragments.updated     == lstats.fragments.updated);
        }
        
        void
        process_line_strip(pipeline::fixed::base& ppl)
        {
          TRACE("hugh::render::software::test::process_line_strip");
          
          using line_strip  = primitive::line_strip;
          using index_list  = line_strip::index_list_type;
          using vertex_list = line_strip::vertex_list_type;
    
          auto const&    vp    (*(*ppl.rasterizer)->viewport);
          unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(100)));
          vertex_list    vl;
    
          for (unsigned x(vp.x); x < (vp.x + vp.width); x += stride) {
            for (unsigned y(vp.y); y < (vp.y + vp.height); y += stride) {
              vl.push_back(vertex(glm::vec3(       x,        y, 0.25)));
              vl.push_back(vertex(glm::vec3(x+stride, y+stride, 0.75)));
              vl.push_back(vertex(glm::vec3(       x,        y, 0.75)));
            }
          }

          {
            line_strip const l(vl);
    
            ppl.process(l);
          }

          auto const lstats(*ppl.stats);
    
          {
            index_list il(vl.size());

            std::iota(il.begin(), il.end(), 0);
      
            line_strip const l(vl, il);
    
            ppl.process(l);
          }
    
          auto const ilstats(*ppl.stats);

          BOOST_CHECK(ilstats.vertices.transformed  >  lstats.vertices.transformed);
          BOOST_CHECK(ilstats.fragments.created     >  lstats.fragments.created);
          BOOST_CHECK(ilstats.fragments.zculled     >  lstats.fragments.zculled);
          BOOST_CHECK(ilstats.fragments.shaded      == lstats.fragments.shaded);
          BOOST_CHECK(ilstats.fragments.ztestfailed == lstats.fragments.ztestfailed);
          BOOST_CHECK(ilstats.fragments.updated     == lstats.fragments.updated);
        }
        
        void
        process_triangle_list(pipeline::fixed::base& ppl)
        {
          TRACE("hugh::render::software::test::process_triangle_list");
          
          using triangle_list = primitive::triangle_list;
          using index_list    = triangle_list::index_list_type;
          using vertex_list   = triangle_list::vertex_list_type;
  
    
          auto const&    vp    (*(*ppl.rasterizer)->viewport);
          unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(50)));
          vertex_list    vl;
    
          for (unsigned x(vp.x); x < (vp.x + vp.width); x += stride) {
            for (unsigned y(vp.y); y < (vp.y + vp.height); y += stride) {
              // ccw -> fragments
              vl.push_back(vertex(glm::vec3(       x,        y, 0.25)));
              vl.push_back(vertex(glm::vec3(x+stride,        y, 0.35)));
              vl.push_back(vertex(glm::vec3(       x, y+stride, 0.45)));
              // cw -> !fragments
              vl.push_back(vertex(glm::vec3(       x,        y, 0.25)));
              vl.push_back(vertex(glm::vec3(       x, y+stride, 0.45)));
              vl.push_back(vertex(glm::vec3(x+stride,        y, 0.35)));
            }
          }

          {
            triangle_list const t(vl);
    
            ppl.process(t);
          }

          auto const lstats(*ppl.stats);
    
          {
            index_list il(vl.size());

            std::iota(il.begin(), il.end(), 0);
      
            triangle_list const l(vl, il);
    
            ppl.process(l);
          }
    
          auto const ilstats(*ppl.stats);

          BOOST_CHECK(ilstats.vertices.transformed  >  lstats.vertices.transformed);
          BOOST_CHECK(ilstats.fragments.created     >  lstats.fragments.created);
          BOOST_CHECK(ilstats.fragments.zculled     >  lstats.fragments.zculled);
          BOOST_CHECK(ilstats.fragments.shaded      == lstats.fragments.shaded);
          BOOST_CHECK(ilstats.fragments.ztestfailed == lstats.fragments.ztestfailed);
          BOOST_CHECK(ilstats.fragments.updated     == lstats.fragments.updated);
        }
        
        void
        process_triangle_strip(pipeline::fixed::base& ppl)
        {
          TRACE("hugh::render::software::test::process_triangle_strip");
          
          using triangle_strip = primitive::triangle_strip;
          using index_list     = triangle_strip::index_list_type;
          using vertex_list    = triangle_strip::vertex_list_type;
    
          auto const&    vp    (*(*ppl.rasterizer)->viewport);
          unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(50)));
          vertex_list    vl;
    
          for (unsigned x(vp.x); x < (vp.x + vp.width); x += stride) {
            for (unsigned y(vp.y); y < (vp.y + vp.height); y += stride) {
              // ccw -> fragments
              vl.push_back(vertex(glm::vec3(       x,        y, 0.25)));
              vl.push_back(vertex(glm::vec3(x+stride,        y, 0.35)));
              vl.push_back(vertex(glm::vec3(       x, y+stride, 0.45)));
              // cw -> !fragments
              vl.push_back(vertex(glm::vec3(       x,        y, 0.25)));
              vl.push_back(vertex(glm::vec3(       x, y+stride, 0.45)));
              vl.push_back(vertex(glm::vec3(x+stride,        y, 0.35)));
            }
          }

          {
            triangle_strip const t(vl);
    
            ppl.process(t);
          }

          auto const lstats(*ppl.stats);
    
          {
            index_list il(vl.size());

            std::iota(il.begin(), il.end(), 0);
      
            triangle_strip const l(vl, il);
    
            ppl.process(l);
          }
    
          auto const ilstats(*ppl.stats);

          BOOST_CHECK(ilstats.vertices.transformed  >  lstats.vertices.transformed);
          BOOST_CHECK(ilstats.fragments.created     >  lstats.fragments.created);
          BOOST_CHECK(ilstats.fragments.zculled     >  lstats.fragments.zculled);
          BOOST_CHECK(ilstats.fragments.shaded      == lstats.fragments.shaded);
          BOOST_CHECK(ilstats.fragments.ztestfailed == lstats.fragments.ztestfailed);
          BOOST_CHECK(ilstats.fragments.updated     == lstats.fragments.updated);
        }
          
      } // namespace test {

    } // namespace software {
  
  } // namespace render {
  
} // namespace hugh {
