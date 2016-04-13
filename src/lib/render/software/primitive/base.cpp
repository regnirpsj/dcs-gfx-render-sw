// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/base.cpp                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/primitive/base.hpp"

// includes, system

#include <ostream> // std::ostream

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

      namespace primitive {
        
        // variables, exported
  
        // functions, exported
      
        /* virtual */
        base::~base()
        {
          TRACE("hugh::render::software::primitive::base::~base");
        }

        /* virtual */ void
        base::print_on(std::ostream& os) const
        {
          TRACE_NEVER("hugh::render::software::primitive::base::print_on");

          os << '['
             << "t:" << unsigned(type) << ','
             << ']';
        }
        
        /* explicit */
        base::base(primitive::type a)
          : support::printable(), type(a)
        {
          TRACE("hugh::render::software::primitive::base::base");
        }
        
      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
