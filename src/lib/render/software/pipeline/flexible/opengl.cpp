// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/flexible/opengl.cpp                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/pipeline/flexible/opengl.hpp"

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
          opengl::opengl()
            : base()
          {
            TRACE("hugh::render::software::pipeline::flexible::opengl::opengl");
          }
        
          /* virtual */
          opengl::~opengl()
          {
            TRACE("hugh::render::software::pipeline::flexible::opengl::~opengl");
          }

          /* virtual */ glm::vec3
          opengl::ndc_to_window(glm::vec3 const& a) const
          {
            TRACE("hugh::render::software::pipeline::flexible::opengl::ndc_to_window");

            rasterizer::base::viewport_type const& vp(*(*rasterizer)->viewport);
            glm::vec3                              result;

            // glspec43.core20120806:13.6.1
            result.x  = ((a.x + 1) * (vp.width  / 2.0f))          + vp.x;
            result.y  = ((a.y + 1) * (vp.height / 2.0f))          + vp.y;
            result.z  = ((a.z      * ((vp.far - vp.near) / 2.0f)) + ((vp.near + vp.far) / 2.0f));
          
            return result;
          }

        } // namespace flexible {
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
