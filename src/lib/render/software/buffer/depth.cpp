// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/buffer/depth.cpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/buffer/depth.hpp"

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
        depth::depth(viewport_type const& a)
          : base       (a),
            clear_value(*this, "clear_value", glm::vec1(viewport->far)),
            buffer_    ((viewport->width-viewport->x) * (viewport->height-viewport->y),
                        *clear_value)
            
        {
          TRACE("hugh:render::software::buffer::depth::depth");
        }
      
        /* virtual */
        depth::~depth()
        {
          TRACE("hugh:render::software::buffer::depth::~depth");
        }
      
        /* virtual */ void
        depth::clear()
        {
          TRACE("hugh:render::software::buffer::depth::clear");

          buffer_ = buffer_type(buffer_.size(), *clear_value);
        }

        /* virtual */ bool
        depth::update(fragment const& f)
        {
          TRACE("hugh:render::software::buffer::depth::update");

          return ztest(f);
        }
        
        /* virtual */ bool
        depth::zcull(fragment const& f) const
        {
          TRACE("hugh:render::software::buffer::depth::zcull");
          
          bool result(true);
          
          if (!(viewport->near > f.depth)) {
            auto const idx(f.position.y * (viewport->width-viewport->x) + f.position.x);
            
            if ((buffer_.size() > idx) && (f.depth < buffer_[idx].x)) {
              result = false;
            }
          }
          
          return result;
        }
        
        /* virtual */ bool
        depth::ztest(fragment const& f)
        {
          TRACE("hugh:render::software::buffer::depth::ztest");
          
          bool result(!zcull(f));
          
          if (result) {
            auto const idx(f.position.y * (viewport->width-viewport->x) + f.position.x);
            
            buffer_[idx].x = f.depth;
          }
          
          return result;
        }

        /* virtual */ void
        depth::do_changed(field::base& f)
        {
          TRACE("hugh:render::software::buffer::depth::do_changed");

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
