// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/line.cpp                                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/line.hpp"

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
      line::line(vertex const& a, vertex const& b)
        : support::printable(),
          p0                (a),
          p1                 (b)
      {
        TRACE("hugh::render::software::line::line");
      }
      
      /* virtual */
      line::~line()
      {
        TRACE("hugh::render::software::line::~line");
      }

      /* virtual */ void
      line::print_on(std::ostream& os) const
      {
        TRACE_NEVER("hugh::render::software::line::print_on");

        os << '['
           << "0:" << p0 << ','
           << "1:" << p1
           << ']';
      }
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
