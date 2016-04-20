// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/pipeline_fixed_direct3d.cpp                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

// #include <>

// includes, project

#include <hugh/render/software/buffer/color.hpp>
#include <hugh/render/software/buffer/depth.hpp>
#include <hugh/render/software/pipeline/fixed/direct3d.hpp>
#include <hugh/render/software/rasterizer/simple.hpp>

#include <pipeline_fixed_shared.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_software_pipeline_fixed_process)
{
  TRACE("test_hugh_render_software_pipeline_fixed_direct3d_process");
  
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;

  viewport const            vp(test::default_viewport);
  pipeline::fixed::direct3d ppl;

  ppl.rasterizer  = new rasterizer::simple(vp);
  ppl.colorbuffer = new buffer::color     (vp);
  ppl.depthbuffer = new buffer::depth     (vp);
  
  (*ppl.depthbuffer)->clear(); test::process_point_list    (ppl);
  (*ppl.depthbuffer)->clear(); test::process_line_list     (ppl);
  (*ppl.depthbuffer)->clear(); test::process_line_strip    (ppl);
  (*ppl.depthbuffer)->clear(); test::process_triangle_list (ppl);
  (*ppl.depthbuffer)->clear(); test::process_triangle_strip(ppl);
}
