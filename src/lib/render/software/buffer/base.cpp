// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/buffer/base.cpp                                            */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/buffer/base.hpp"

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

      namespace buffer {
        
        // variables, exported
  
        // functions, exported

        /* virtual */
        base::~base()
        {
          TRACE("hugh:render::software::base::~base");
        }

#if 0
        /* virtual */ void
        base::clear()
        {
          TRACE("hugh:render::software::base::clear");

          throw std::logic_error("pure virtual function 'hugh:render::software::base::clear' "
                                 "called");
        }
#endif
        
        /* virtual */ bool
        base::update(fragment const&)
        {
          TRACE("hugh:render::software::base::update");

          throw std::logic_error("pure virtual function 'hugh:render::software::base::update' "
                                 "called");

          return false;
        }

        /* explicit */
        base::base(viewport_type const& a)
          : field::container         (),
            support::refcounted<base>(),
            viewport                 (*this, "viewport", a)
        {
          TRACE("hugh:render::software::base::base");
        }

      } // namespace buffer {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
