// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/triangles.cpp                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/primitive/triangles.hpp"

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
        triangles::triangles()
          : base(primitive::type::triangles)
        {
          TRACE("hugh::render::software::primitive::triangles::triangles");
        }
        
        /* virtual */
        triangles::~triangles()
        {
          TRACE("hugh::render::software::primitive::triangles::~triangles");
        }

      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
