// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/lines.cpp                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/primitive/lines.hpp"

// includes, system

//#include <>

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

        /* explicit */
        lines::lines()
          : base(primitive::type::lines)
        {
          TRACE("hugh::render::software::primitive::lines::lines");
        }
        
        /* virtual */
        lines::~lines()
        {
          TRACE("hugh::render::software::primitive::lines::~lines");
        }
        
      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
