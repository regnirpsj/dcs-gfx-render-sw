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

#include <boost/io/ios_state.hpp> // boost::io::ios_all_saver
#include <iomanip>                // std::setw
#include <stdexcept>              // std::logic_error

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

        base::statistics::statistics()
          : points(0), lines(0), triangles(0)
        {
          TRACE("hugh::render::software::rasterizer::base::statistics::statistics");
        }

        void
        base::statistics::reset()
        {
          TRACE("hugh::render::software::rasterizer::base::statistics::reset");

          points    = 0;
          lines     = 0;
          triangles = 0;
        }

        base::statistics&
        base::statistics::operator+=(statistics const& a)
        {
          TRACE_NEVER("hugh::render::software::rasterizer::base::statistics::operator+=");

          points    = a.points;
          lines     = a.lines;
          triangles = a.triangles;
          
          return *this;
        }
        
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

          return fragment_list_type();
        }
        
        /* virtual */ base::fragment_list_type
        base::process(vertex const&, vertex const&) const
        {
          TRACE_NEVER("hugh::render::software::rasterizer::base::process(line)");

          throw std::logic_error("pure virtual function "
                                 "'hugh::render::software::rasterizer::base::process(line)' "
                                 "called");

          return fragment_list_type();
        }
      
        /* virtual */ base::fragment_list_type
        base::process(vertex const&, vertex const&, vertex const&) const
        {
          TRACE_NEVER("hugh::render::software::rasterizer::base::process(triangle)");
        
          throw std::logic_error("pure virtual function "
                                 "'hugh::render::software::rasterizer::base::process(triangle)' "
                                 "called");

          return fragment_list_type();
        }
      
        /* explicit */
        base::base(viewport_type const& a)
          : field::container         (),
            support::refcounted<base>(),
            viewport                 (*this, "viewport", a),
            stats                    (*this, "stats")
        {
          TRACE("hugh::render::software::rasterizer::base::base");
        }

        std::ostream&
        operator<<(std::ostream& os, base::statistics const& a)
        {
          TRACE_NEVER("hugh::render::software::rasterizer::operator<<(base::statistics)");

          std::ostream::sentry const cerberus(os);

          if (cerberus) {
            boost::io::ios_all_saver const ias(os);

            static unsigned const width(7);
            
            os << '['
               << "p:"
               << std::setw(width) << a.points
               << ",l:"
               << std::setw(width) << a.lines
               << ",t:"
               << std::setw(width) << a.triangles
               << ']';
          }

          return os;
        }
        
      } // namespace rasterizer {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
