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
            buffer_     ((viewport->width-viewport->x) * (viewport->height-viewport->y),
                         glm::vec1(1))
            
        {
          TRACE("hugh:render::software::depth::depth");
        }
      
        /* virtual */
        depth::~depth()
        {
          TRACE("hugh:render::software::depth::~depth");
        }
      
        /* virtual */ void
        depth::clear(glm::vec1 const& a)
        {
          TRACE("hugh:render::software::depth::clear");

          buffer_ = buffer_type(buffer_.size(), a);
        }

        /* virtual */ bool
        depth::update(fragment const& f)
        {
          TRACE("hugh:render::software::depth::update");

          return ztest(f);
        }
        
        /* virtual */ bool
        depth::zcull(fragment const& f) const
        {
          TRACE("hugh:render::software::depth::zcull");
          
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
          TRACE("hugh:render::software::depth::ztest");
          
          bool result(!zcull(f));
          
          if (result) {
            auto const idx(f.position.y * (viewport->width-viewport->x) + f.position.x);
            
            buffer_[idx].x = f.depth;
          }
          
          return result;
        }

      } // namespace buffer {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
