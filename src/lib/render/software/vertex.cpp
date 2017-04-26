// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016-2017 University of Hull                                                     */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/vertex.cpp                                                 */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/vertex.hpp"

// includes, system

#include <glm/gtx/io.hpp> // glm::operator<<
#include <ostream>        // std::ostream

// includes, project

#include <hugh/support/io.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {

  namespace render {

    namespace software {
      
      // variables, exported
  
      // functions, exported

      /* explicit */
      vertex::vertex(glm::vec3 const& a, attribute::list const& b)
        : support::printable(), position(a), attributes(b)
      {
        TRACE("hugh::render::software::vertex::vertex");
      }
      
      /* virtual */
      vertex::~vertex()
      {
        TRACE("hugh::render::software::vertex::~vertex");
      }

      /* virtual */ void
      vertex::print_on(std::ostream& os) const
      {
        TRACE_NEVER("hugh::render::software::vertex::print_on");

        using support::ostream::operator<<;
        
        os << '['
           << "p:" << position   << ','
           << "a:" << attributes
           << ']';
      }
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
