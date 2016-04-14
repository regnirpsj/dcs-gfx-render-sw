// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/primitive_point_list.cpp                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <sstream> // std::ostringstream

// includes, project

#include <hugh/render/software/primitive/point_list.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_software_primitive_point_list_ctor)
{
  using namespace hugh::render::software;
  using point_list  = primitive::point_list;
  using vertex_list = point_list::vertex_list_type;

  {
    vertex_list const v;
    
    BOOST_REQUIRE_THROW(point_list const p(v), std::exception);
  }

  {
    vertex_list const v(1, vertex(glm::vec3()));
    point_list const  p(v);
    
    BOOST_CHECK(1 == p.vertices.size());
    BOOST_CHECK(     p.indices.empty());
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_primitive_point_list_print_on)
{
  using namespace hugh::render::software;
  using point_list  = primitive::point_list;
  using vertex_list = point_list::vertex_list_type;

  vertex_list const  v(1, vertex(glm::vec3()));
  point_list const   p(v);
  std::ostringstream ostr;

  ostr << p;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
