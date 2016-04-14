// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/point_list.cpp                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/primitive/point_list.hpp"

// includes, system

#include <stdexcept> // std::out_of_range

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
        point_list::point_list(vertex_list_type const& a, index_list_type const& b)
          : base(primitive::topology::point_list, a, b)
        {
          TRACE("hugh::render::software::primitive::point_list::point_list");

          if (1 > vertices.size()) {
            throw std::out_of_range("<render::software::primitive::point_list>: "
                                    "requires at least 1 vertex");
          }
        }
        
        /* virtual */
        point_list::~point_list()
        {
          TRACE("hugh::render::software::primitive::point_list::~point_list");
        }
        
      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
