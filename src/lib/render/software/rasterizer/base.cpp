// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/rasterizer/base.cpp                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/rasterizer/base.hpp"

// includes, system

#include <stdexcept> // std::logic_error

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

      namespace rasterizer {
        
        // variables, exported
  
        // functions, exported

        /* virtual */
        base::~base()
        {
          TRACE("hugh::render::software::rasterizer::base::~base");
        }

        /* virtual */ base::fragment_list_type
        base::process(vertex const&) const
        {
          TRACE_NEVER("hugh::render::software::rasterizer::base::process(vertex)");

          throw std::logic_error("pure virtual function "
                                 "'hugh::render::software::rasterizer::base::process(vertex)' "
                                 "called");
        }
        
        /* virtual */ base::fragment_list_type
        base::process(line const&) const
        {
          TRACE_NEVER("hugh::render::software::rasterizer::base::process(line)");

          throw std::logic_error("pure virtual function "
                                 "'hugh::render::software::rasterizer::base::process(line)' "
                                 "called");
        }
      
        /* virtual */ base::fragment_list_type
        base::process(triangle const&) const
        {
          TRACE_NEVER("hugh::render::software::rasterizer::base::process(triangle)");
        
          throw std::logic_error("pure virtual function "
                                 "'hugh::render::software::rasterizer::base::process(triangle)' "
                                 "called");
        }
      
        /* explicit */
        base::base(viewport_type const& a)
          : support::refcounted<base>(),
            viewport_                (a)
        {
          TRACE("hugh::render::software::rasterizer::base::base");
        }

      } // namespace rasterizer {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
