// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/context.cpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <sstream> // std::ostringstream

// includes, project

#include <hugh/render/software/context.hpp>
#include <hugh/render/software/pipelines.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_software_context_ctor)
{
  using namespace hugh::render::software;

  std::unique_ptr<context> const c(new context(new pipeline::fixed::opengl));

  BOOST_CHECK(nullptr != c);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_context_clear)
{
  using namespace hugh::render::software;

  std::unique_ptr<context> c(new context(new pipeline::fixed::opengl));

  BOOST_CHECK(nullptr != c);

  c->clear();
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_context_submit)
{
  using namespace hugh::render::software;

  std::unique_ptr<context> c(new context(new pipeline::fixed::opengl));

  BOOST_CHECK(nullptr != c);

  c->submit();
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_context_flush)
{
  using namespace hugh::render::software;

  std::unique_ptr<context> c(new context(new pipeline::fixed::opengl));

  BOOST_CHECK(nullptr != c);

  c->flush();
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_context_print_on)
{
  using namespace hugh::render::software;

  context c(new pipeline::fixed::opengl);

  {
    context::eval_manager().evaluate();
    
    c.viewport.touch();
    
    context::eval_manager().evaluate();
    context::eval_manager().evaluate();
  }
  
  std::ostringstream ostr;
  
  ostr << c;
  
  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str() << '\n');
}
