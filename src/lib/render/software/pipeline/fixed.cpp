// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/fixed.cpp                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/pipeline/fixed.hpp"

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

      namespace pipeline {
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        fixed::fixed()
          : base()
        {
          TRACE("hugh::render::software::pipeline::fixed::fixed");
        }
        
        /* virtual */
        fixed::~fixed()
        {
          TRACE("hugh::render::software::pipeline::fixed::~fixed");
        }

        /* virtual */ void
        fixed::process(primitive::base const& p)
        {
          TRACE("hugh::render::software::pipeline::fixed::process");

          switch (p.type) {
          case primitive::type::points:
            {
            }
            break;

          case primitive::type::lines:
            {
            }
            break;

          case primitive::type::triangles:
            {
            }
            break;

          default:
            break;
          }
          
        }

      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
