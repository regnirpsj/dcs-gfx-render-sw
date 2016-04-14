// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/base.cpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/pipeline/base.hpp"

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

      namespace pipeline {
        
        // variables, exported
  
        // functions, exported

        /* virtual */
        base::~base()
        {
          TRACE("hugh::render::software::pipeline::base::~base");
        }

        /* virtual */ void
        base::process(primitive::base const&)
        {
          TRACE_NEVER("hugh::render::software::pipeline::base::process");

          throw std::logic_error("pure virtual function "
                                 "'hugh::render::software::pipeline::base::process' called");
        }
          
        /* explicit */
        base::base()
          : field::container         (),
            support::refcounted<base>(),
            xform_model              (*this, "xform_model"),
            xform_view               (*this, "xform_view"),
            xform_projection         (*this, "xform_projection"),
            lights                   (*this, "lights"),
            material                 (*this, "material"),
            rasterizer               (*this, "rasterizer",  nullptr),
            depthbuffer              (*this, "depthbuffer", nullptr),
            framebuffer              (*this, "framebuffer", nullptr),
            count_                   ()
        {
          TRACE("hugh::render::software::pipeline::base::base");
        }

        glm::vec4
        base::object_to_world(glm::vec4 const& a) const
        {
          TRACE("hugh::render::software::pipeline::base::object_to_world");

          return (*xform_model * a);
        }
        
        glm::vec4
        base::world_to_eye(glm::vec4 const& a) const
        {
          TRACE("hugh::render::software::pipeline::base::world_to_eye");

          return (*xform_view * a);
        }
        
        glm::vec4
        base::eye_to_clip(glm::vec4 const& a) const
        {
          TRACE("hugh::render::software::pipeline::base::eye_to_clip");

          return (*xform_projection * a);
        }
        
        glm::vec3
        base::clip_to_ndc(glm::vec4 const& a) const
        {
          TRACE("hugh::render::software::pipeline::base::clip_to_ndc");

          return glm::vec3(a.x / a.w, a.y / a.w, a.z / a.w);
        }
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
