// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/flexible/direct3d.cpp                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/pipeline/flexible/direct3d.hpp"

// includes, system

//#include <>

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

      namespace pipeline {

        namespace flexible {
          
          // variables, exported
  
          // functions, exported

          /* explicit */
          direct3d::direct3d()
            : base()
          {
            TRACE("hugh::render::software::pipeline::flexible::direct3d::direct3d");
          }
        
          /* virtual */
          direct3d::~direct3d()
          {
            TRACE("hugh::render::software::pipeline::flexible::direct3d::~direct3d");
          }

          /* virtual */ glm::vec3
          direct3d::ndc_to_window(glm::vec3 const& a) const
          {
            TRACE("hugh::render::software::pipeline::flexible::direct3d::ndc_to_window");

            rasterizer::base::viewport_type const& vp(*(*rasterizer)->viewport);
            glm::vec3                              result;

            // http://msdn.microsoft.com/en-us/library/windows/desktop/bb205126%28v=vs.85%29.aspx
            result.x = ((a.x + 1) * (vp.width  / 2.0f)) + vp.x;
            result.y = ((1 - a.y) * (vp.height / 2.0f)) + vp.y;
            result.z = ( a.z      * (vp.far - vp.near)) + vp.near;

            return result;
          }

        } // namespace flexible {
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
