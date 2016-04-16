// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/pipeline/fixed.cpp                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <memory>  // std::unique_ptr<>
#include <sstream> // std::ostringstream

// includes, project

#include <hugh/render/software/buffer/color.hpp>
#include <hugh/render/software/buffer/depth.hpp>
#include <hugh/render/software/pipeline/fixed.hpp>
#include <hugh/render/software/primitives.hpp>
#include <hugh/render/software/rasterizer/simple.hpp>

#define HUGH_USE_TRACE
//#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_render_software_pipeline_fixed_ctor)
{
  using namespace hugh::render::software;

  std::unique_ptr<pipeline::base> const p(new pipeline::fixed);
  
  BOOST_CHECK(nullptr != p);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_pipeline_fixed_process)
{
  TRACE("test_hugh_render_software_pipeline_fixed_process");
  
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;

  //viewport const  vp(0, 0, 80, 60, 0, 1);
  //viewport const  vp(0, 0, 160, 120, 0, 1);
  viewport const  vp(0, 0, 320, 240, 0, 1);
  //viewport const  vp(0, 0, 1600, 1200, 0, 1);
  pipeline::fixed ppl;

  ppl.rasterizer  = new rasterizer::simple(vp);
  ppl.colorbuffer = new buffer::color(vp);
  ppl.depthbuffer = new buffer::depth(vp);

  {
    using point_list  = primitive::point_list;
    using index_list  = point_list::index_list_type;
    using vertex_list = point_list::vertex_list_type;
  
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(200)));
    
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

    BOOST_CHECK(ilstats.vertices.processed >  lstats.vertices.processed);
    BOOST_CHECK(ilstats.fragments.created  >  lstats.fragments.created);
    BOOST_CHECK(ilstats.fragments.updated  == lstats.fragments.updated);
  }
  
  {
    using line_list   = primitive::line_list;
    using index_list  = line_list::index_list_type;
    using vertex_list = line_list::vertex_list_type;
    
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(100)));
    
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

    BOOST_CHECK(ilstats.vertices.processed >  lstats.vertices.processed);
    BOOST_CHECK(ilstats.fragments.created  >  lstats.fragments.created);
    BOOST_CHECK(ilstats.fragments.updated  == lstats.fragments.updated);
  }
  
  {
    using line_strip  = primitive::line_strip;
    using index_list  = line_strip::index_list_type;
    using vertex_list = line_strip::vertex_list_type;
    
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(100)));
    
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

    BOOST_CHECK(ilstats.vertices.processed >  lstats.vertices.processed);
    BOOST_CHECK(ilstats.fragments.created  >  lstats.fragments.created);
    BOOST_CHECK(ilstats.fragments.updated  == lstats.fragments.updated);
  }
  
  {
    using triangle_list = primitive::triangle_list;
    using index_list    = triangle_list::index_list_type;
    using vertex_list   = triangle_list::vertex_list_type;
  
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(50)));
    
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

    BOOST_CHECK(ilstats.vertices.processed >  lstats.vertices.processed);
    BOOST_CHECK(ilstats.fragments.created  >  lstats.fragments.created);
    BOOST_CHECK(ilstats.fragments.updated  == lstats.fragments.updated);
  }
  
  {
    using triangle_strip = primitive::triangle_strip;
    using index_list     = triangle_strip::index_list_type;
    using vertex_list    = triangle_strip::vertex_list_type;
  
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/std::min(vp.width-vp.x, float(50)));
    
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

    BOOST_CHECK(ilstats.vertices.processed >  lstats.vertices.processed);
    BOOST_CHECK(ilstats.fragments.created  >  lstats.fragments.created);
    BOOST_CHECK(ilstats.fragments.updated  == lstats.fragments.updated);
  }
}
