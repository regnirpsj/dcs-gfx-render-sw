// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016-2017 University of Hull                                                     */
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

          using support::ostream::operator<<;
          
          os << '['
             << "t:" << topology << ','
             << "v:" << vertices.size() << ':' << vertices << ','
             << "i:" << indices .size() << ':' << indices
             << ']';
        }
        
        /* explicit */
        base::base(primitive::topology a, vertex_list_type const& b, index_list_type const& c)
          : support::printable(),
            topology          (a),
            vertices          (b),
            indices           (c)
        {
          TRACE("hugh::render::software::primitive::base::base");
        }

        std::ostream&
        operator<<(std::ostream& os, topology const& a)
        {
          TRACE_NEVER("hugh::render::software::primitive::operator<<(topology)");

          std::ostream::sentry const cerberus(os);

          if (cerberus) {
            os << '[';
            
            switch (a) {
            case primitive::topology::point_list:     os << "POINT_LIST";     break;
            case primitive::topology::line_list:      os << "LINE_LIST";      break;
            case primitive::topology::line_strip:     os << "LINE_STRIP";     break;
            case primitive::topology::triangle_list:  os << "TRIANGLE_LIST";  break;
            case primitive::topology::triangle_strip: os << "TRIANGLE_STRIP"; break;
            default: os << "UNKNOWN (" << unsigned(a) << ')'; break;
            }

            os << ']';
          }

          return os;
        }
        
      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
