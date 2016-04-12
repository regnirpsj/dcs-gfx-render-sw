// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/fragment.cpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <sstream> // std::ostringstream

// includes, project

#include <hugh/render/software/fragment.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_software_fragment_ctor)
{
  using hugh::render::software::fragment;

  fragment const f(glm::uvec2(0, 0), 0.0);
  
  BOOST_CHECK(glm::uvec2(0, 0) == f.position);
  BOOST_CHECK(0.0              == f.depth);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_fragment_print_on)
{
  using hugh::render::software::fragment;

  fragment const     f(glm::uvec2(0, 0), 0.0);
  std::ostringstream ostr;

  ostr << f;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
