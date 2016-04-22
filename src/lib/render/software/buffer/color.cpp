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

#include <glm/gtx/io.hpp> // glm::operator<<
#include <stdexcept>      // std::logic_error

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
          : base       (a),
            clear_value(*this, "clear_value", glm::vec4(0,0,0,0)),
            buffer_    ((viewport->width-viewport->x) * (viewport->height-viewport->y),
                        *clear_value)
        {
          TRACE("hugh:render::software::buffer::color::color");
        }
      
        /* virtual */
        color::~color()
        {
          TRACE("hugh:render::software::buffer::color::~color");
        }
      
        /* virtual */ void
        color::clear()
        {
          TRACE("hugh:render::software::buffer::color::clear");

          buffer_ = buffer_type(buffer_.size(), *clear_value);
        }

        /* virtual */ bool
        color::update(fragment const& f)
        {
          TRACE("hugh:render::software::buffer::color::update");

          bool       result(false);
          auto const idx   (f.position.y * (viewport->width-viewport->x) + f.position.x);

          if (buffer_.size() > idx) {
            buffer_[idx] = glm::clamp(const_cast<attribute::list&>(f.attributes)[attribute::type::color], glm::vec4(0,0,0,0), glm::vec4(1,1,1,1));
            result       = true;
          }
          
          return result;
        }

        /* virtual */ void
        color::do_changed(field::base& f)
        {
          TRACE("hugh:render::software::buffer::color::do_changed");

          if (&f == &viewport) {
            buffer_.reserve((viewport->width-viewport->x) * (viewport->height-viewport->y));
          }

          else {
            base::do_changed(f);
          }
        }
        
      } // namespace buffer {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
