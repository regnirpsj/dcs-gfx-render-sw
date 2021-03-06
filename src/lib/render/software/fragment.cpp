// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016-2017 University of Hull                                                     */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/fragment.cpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/fragment.hpp"

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
      fragment::fragment(glm::uvec2 const& a, float b, attribute::list const& c)
        : support::printable(), position(a), depth(b), attributes(c)
      {
        TRACE("hugh::render::software::fragment::fragment");
      }
      
      /* virtual */
      fragment::~fragment()
      {
        TRACE("hugh::render::software::fragment::~fragment");
      }
      
      /* virtual */ void
      fragment::print_on(std::ostream& os) const
      {
        TRACE_NEVER("hugh::render::software::fragment::print_on");

        using support::ostream::operator<<;
        
        os << '['
           << "p:" << position   << ','
           << "d:" << depth      << ','
           << "a:" << attributes
           << ']';
      }
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
