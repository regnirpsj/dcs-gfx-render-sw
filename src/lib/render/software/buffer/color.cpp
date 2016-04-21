// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/buffer/color.cpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/buffer/color.hpp"

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

        /* explicit */
        color::color(viewport_type const& a)
          : base        (a),
            buffer_     ((viewport->width-viewport->x) * (viewport->height-viewport->y),
                         glm::vec4(0,0,0,0))
        {
          TRACE("hugh:render::software::color::color");
        }
      
        /* virtual */
        color::~color()
        {
          TRACE("hugh:render::software::color::~color");
        }
      
        /* virtual */ void
        color::clear(glm::vec4 const& a)
        {
          TRACE("hugh:render::software::color::clear");

          buffer_ = buffer_type(buffer_.size(), a);
        }

        /* virtual */ bool
        color::update(fragment const& f)
        {
          TRACE("hugh:render::software::color::update");

          bool       result(false);
          auto const idx   (f.position.y * (viewport->width-viewport->x) + f.position.x);

          if (buffer_.size() > idx) {
            buffer_[idx] = const_cast<attribute::list&>(f.attributes)[attribute::type::color];
            result       = true;
          }
          
          return result;
        }

      } // namespace buffer {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
