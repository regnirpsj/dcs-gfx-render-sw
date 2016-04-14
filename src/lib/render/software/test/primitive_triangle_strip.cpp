// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/primitive_triangle_strip.cpp                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <sstream> // std::ostringstream

// includes, project

#include <hugh/render/software/primitive/triangle_strip.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_software_primitive_triangle_strip_ctor)
{
  using namespace hugh::render::software;
  using vertex_list_type = primitive::triangle_strip::vertex_list_type;

  vertex_list_type const          v;
  primitive::triangle_strip const p(v);
  
  BOOST_CHECK(p.vertices.empty());
  BOOST_CHECK(p.indices.empty());
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_primitive_triangle_strip_print_on)
{
  using namespace hugh::render::software;
  using vertex_list_type = primitive::triangle_strip::vertex_list_type;

  vertex_list_type const          v;
  primitive::triangle_strip const p(v);
  std::ostringstream              ostr;

  ostr << p;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
