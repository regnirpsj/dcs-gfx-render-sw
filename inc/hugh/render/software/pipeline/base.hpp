// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/base.hpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_BASE_HPP)

#define HUGH_RENDER_SOFTWARE_PIPELINE_BASE_HPP

// includes, system

#include <boost/intrusive_ptr.hpp> // boost::intrusive_ptr<>
#include <glm/glm.hpp>             // glm::mat4

// includes, project

#include <hugh/field/container.hpp>
#include <hugh/field/value/multi.hpp>
#include <hugh/field/value/single.hpp>
#include <hugh/render/software/export.h>
#include <hugh/render/software/buffer/depth/base.hpp>
#include <hugh/render/software/buffer/frame/base.hpp>
#include <hugh/render/software/primitive/base.hpp>
#include <hugh/render/software/rasterizer/base.hpp>
#include <hugh/scene/object/light/base.hpp>
#include <hugh/scene/object/material.hpp>
#include <hugh/support/refcounted.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace pipeline {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT base : public field::container,
                                                 public support::refcounted<base> {

        public:

          using light_type       = hugh::scene::object::light::base::rep;
          using material_type    = hugh::scene::object::material::rep;
          using rasterizer_type  = boost::intrusive_ptr<rasterizer::base>;
          using depthbuffer_type = boost::intrusive_ptr<buffer::depth::base>;
          using framebuffer_type = boost::intrusive_ptr<buffer::frame::base>;

          field::value::single<glm::mat4>        xform_model;
          field::value::single<glm::mat4>        xform_view;
          field::value::single<glm::mat4>        xform_projection;
          field::value::multi<light_type>        lights;
          field::value::single<material_type>    material;
          field::value::single<rasterizer_type>  rasterizer;
          field::value::single<depthbuffer_type> depthbuffer;
          field::value::single<framebuffer_type> framebuffer;
          
          virtual ~base();

          virtual void process(primitive::base const&) =0;
          
        protected:

          struct counter {

          public:

            unsigned fragments[2];
            unsigned vertices;
            
          };

          counter count_;
          
          explicit base();

          glm::vec4 object_to_world(glm::vec4 const&) const;
          glm::vec4 world_to_eye   (glm::vec4 const&) const;
          glm::vec4 eye_to_clip    (glm::vec4 const&) const;
          glm::vec3 clip_to_ndc    (glm::vec4 const&) const;
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_BASE_HPP)
