// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/triangle.cpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/triangle.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_software_triangle_ctor)
{
  using hugh::render::software::triangle;

  triangle const t(glm::vec3(0, 0, 0),glm::vec3(1, 0, 0), glm::vec3(0, 1, 0));
  
  BOOST_CHECK(glm::vec3(0, 0, 0) == t.p0);
  BOOST_CHECK(glm::vec3(1, 0, 0) == t.p1);
  BOOST_CHECK(glm::vec3(0, 1, 0) == t.p2);
  BOOST_CHECK(glm::vec3(0, 0, 1) == t.n);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_triangle_print_on)
{
  using hugh::render::software::triangle;

  triangle const     t(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 1, 0));
  std::ostringstream ostr;

  ostr << t;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
