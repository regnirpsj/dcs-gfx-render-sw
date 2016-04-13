// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/triangle.cpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/triangle.hpp"

// includes, system

#include <glm/gtx/io.hpp> // glm::operator<<
#include <ostream>        // std::ostream

// includes, project

//#include <>

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
      triangle::triangle(vertex const& a, vertex const& b, vertex const& c)
        : support::printable(),
          p0                (a),
          p1                (b),
          p2                (c),
          n                 (glm::normalize(glm::cross(p1.position-p0.position,
                                                       p2.position-p0.position)))
      {
        TRACE("hugh::render::software::triangle::triangle");
      }
      
      /* virtual */
      triangle::~triangle()
      {
        TRACE("hugh::render::software::triangle::~triangle");
      }

      /* virtual */ void
      triangle::print_on(std::ostream& os) const
      {
        TRACE_NEVER("hugh::render::software::triangle::print_on");

        os << '['
           << "0:" << p0 << ','
           << "1:" << p1 << ','
           << "2:" << p2 << ','
           << "n:" << n
           << ']';
      }
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
