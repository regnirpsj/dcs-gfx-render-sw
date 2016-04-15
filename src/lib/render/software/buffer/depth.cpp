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
        depth::depth(viewport_type const& a)
          : base        (a),
            clear_value_(glm::vec1(viewport_.far)),
            buffer_     ((viewport_.width-viewport_.x) * (viewport_.height-viewport_.y),
                         clear_value_)
            
        {
          TRACE("hugh:render::software::depth::depth");
        }
      
        /* virtual */
        depth::~depth()
        {
          TRACE("hugh:render::software::depth::~depth");
        }
      
        /* virtual */ void
        depth::clear()
        {
          TRACE("hugh:render::software::depth::clear");

          buffer_ = buffer_type(buffer_.size(), clear_value_);
        }

        /* virtual */ bool
        depth::update(fragment const& f)
        {
          TRACE("hugh:render::software::depth::update");

          bool result(false);

          if (!(viewport_.near > f.depth)) {
            auto const idx(f.position.y * (viewport_.width-viewport_.x) + f.position.x);

            if ((buffer_.size() > idx) && (f.depth < buffer_[idx].x)) {
              buffer_[idx].x = f.depth;
              result         = true;
            }
          }
          
          return result;
        }

      } // namespace buffer {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
