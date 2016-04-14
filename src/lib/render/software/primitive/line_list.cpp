// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/line_list.cpp                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/primitive/line_list.hpp"

// includes, system

#include <stdexcept> // std::logic_error, std::out_of_range

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
        line_list::line_list(vertex_list_type const& a, index_list_type const& b)
          : base(primitive::topology::line_list, a, b)
        {
          TRACE("hugh::render::software::primitive::line_list::line_list");
          
          if (2 > vertices.size()) {
            throw std::out_of_range("<render::software::primitive::line_list>: "
                                    "requires at least 2 vertices");
          }

          if (vertices.size() % 2) {
            throw std::logic_error("<render::software::primitive::line_list>: "
                                   "requires number of vertices divisible by 2");
          }
        }
        
        /* virtual */
        line_list::~line_list()
        {
          TRACE("hugh::render::software::primitive::line_list::~line_list");
        }
        
      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
