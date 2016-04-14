// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/attribute.cpp                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <array>          // std::array<>
#include <glm/gtx/io.hpp> // glm::operator<<
#include <sstream>        // std::ostringstream

// includes, project

#include <hugh/render/software/attribute.hpp>
#include <hugh/support/io_utils.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_render_software_attribute_type)
{
  using namespace hugh::render::software;

  std::array<attribute::type const, 5> const types = {
    {
      attribute::type::position,
      attribute::type::normal,
      attribute::type::color,
      attribute::type::texcoord,
      attribute::type::bitangent,
    }
  };

  for (auto t : types) {
    std::ostringstream ostr;

    ostr << t;
    
    BOOST_CHECK       (!ostr.str().empty());
    BOOST_TEST_MESSAGE( ostr.str());
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_attribute_list)
{
  using namespace hugh::render::software;

  attribute::list const l({ { attribute::type::position,  glm::vec4() },
                            { attribute::type::normal,    glm::vec4() },
                            { attribute::type::color,     glm::vec4() },
                            { attribute::type::texcoord,  glm::vec4() },
                            { attribute::type::bitangent, glm::vec4() }, });
  std::ostringstream    ostr;

  using hugh::support::ostream::operator<<;
  
  ostr << l;
  
  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
