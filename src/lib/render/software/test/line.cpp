// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/line.cpp                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/line.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_software_line_ctor)
{
  using hugh::render::software::line;

  line const l(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
  
  BOOST_CHECK(glm::vec3(0, 0, 0) == l.p0);
  BOOST_CHECK(glm::vec3(1, 1, 1) == l.p1);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_line_print_on)
{
  using hugh::render::software::line;

  line const         l(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
  std::ostringstream ostr;

  ostr << l;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
