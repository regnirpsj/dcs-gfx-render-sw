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
#undef HUGH_USE_TRACE
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
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;

  viewport const  vp(0, 0, 320, 240, 0, 1);
  pipeline::fixed ppl;

  ppl.rasterizer  = new rasterizer::simple(vp);
  ppl.colorbuffer = new buffer::color(vp);
  ppl.depthbuffer = new buffer::depth(vp);

  {
    using point_list  = primitive::point_list;
    using vertex_list = point_list::vertex_list_type;
  
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/100);
    
    for (unsigned x(vp.x); x < (vp.x + vp.width); x += stride) {
      for (unsigned y(vp.y); y < (vp.y + vp.height); y += stride) {
        vl.push_back(vertex(glm::vec3(x, y,  1.5)));  // > vp.far  -> false
        vl.push_back(vertex(glm::vec3(x, y,  0.75))); // < current -> true
        vl.push_back(vertex(glm::vec3(x, y,  0.25))); // < current -> true
        vl.push_back(vertex(glm::vec3(x, y,  0.5)));  // > current -> false
        vl.push_back(vertex(glm::vec3(x, y, -0.25))); // < vp.near -> false
      }
    }
    
    point_list const p(vl);
    
    ppl.process(p);
  }
  
  {
    using line_list   = primitive::line_list;
    using vertex_list = line_list::vertex_list_type;
    
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/50);
    
    for (unsigned x(vp.x); x < (vp.x + vp.width); x += stride) {
      for (unsigned y(vp.y); y < (vp.y + vp.height); y += stride) {
        vl.push_back(vertex(glm::vec3(       x,        y, 0.25)));
        vl.push_back(vertex(glm::vec3(x+stride, y+stride, 0.75)));
        vl.push_back(vertex(glm::vec3(x+stride, y+stride, 0.25)));
        vl.push_back(vertex(glm::vec3(       x,        y, 0.75)));
      }
    }
    
    line_list const l(vl);
    
    ppl.process(l);
  }

  {
    using line_strip  = primitive::line_strip;
    using vertex_list = line_strip::vertex_list_type;
    
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/50);
    
    for (unsigned x(vp.x); x < (vp.x + vp.width); x += stride) {
      for (unsigned y(vp.y); y < (vp.y + vp.height); y += stride) {
        vl.push_back(vertex(glm::vec3(       x,        y, 0.25)));
        vl.push_back(vertex(glm::vec3(x+stride, y+stride, 0.75)));
        vl.push_back(vertex(glm::vec3(       x,        y, 0.75)));
      }
    }
    
    line_strip const l(vl);
    
    ppl.process(l);
  }

  {
    using triangle_list = primitive::triangle_list;
    using vertex_list   = triangle_list::vertex_list_type;
  
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/10);
    
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
    
    triangle_list const t(vl);
    
    ppl.process(t);
  }

  {
    using triangle_strip = primitive::triangle_strip;
    using vertex_list    = triangle_strip::vertex_list_type;
  
    vertex_list    vl;
    unsigned const stride((vp.width-vp.x)/10);
    
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
    
    triangle_strip const t(vl);
    
    ppl.process(t);
  }
  
  BOOST_CHECK(true);
}
