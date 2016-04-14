// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/triangle_strip.cpp                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/primitive/triangle_strip.hpp"

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
        triangle_strip::triangle_strip(vertex_list_type const& a, index_list_type const& b)
          : base(primitive::topology::triangle_strip, a, b)
        {
          TRACE("hugh::render::software::primitive::triangle_strip::triangle_strip");
        }
        
        /* virtual */
        triangle_strip::~triangle_strip()
        {
          TRACE("hugh::render::software::primitive::triangle_strip::~triangle_strip");
        }

      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
