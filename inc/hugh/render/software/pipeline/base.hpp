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
#include <hugh/render/software/buffer/color.hpp>
#include <hugh/render/software/buffer/depth.hpp>
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

          struct statistics {

            struct {

              unsigned created;
              unsigned shaded;
              unsigned updated;
              
            } fragments;
            
            struct {
              
              unsigned processed;
              
            } vertices;

            statistics();
            
            statistics& operator+=(statistics const&);
            
          };
          
          using light_type        = hugh::scene::object::light::base::rep;
          using material_type     = hugh::scene::object::material::rep;
          using rasterizer_type   = boost::intrusive_ptr<rasterizer::base>;
          using color_buffer_type = boost::intrusive_ptr<buffer::color>;
          using depth_buffer_type = boost::intrusive_ptr<buffer::depth>;

          field::value::single<glm::mat4>         xform_model;
          field::value::single<glm::mat4>         xform_view;
          field::value::single<glm::mat4>         xform_projection;
          field::value::multi<light_type>         lights;
          field::value::single<material_type>     material;
          field::value::single<rasterizer_type>   rasterizer;
          field::value::single<color_buffer_type> colorbuffer;
          field::value::single<depth_buffer_type> depthbuffer;
          field::value::single<statistics>        stats;
          
          virtual ~base();

          virtual void process(primitive::base const&) =0;

          glm::vec4 object_to_world(glm::vec4 const&) const;
          glm::vec4 world_to_eye   (glm::vec4 const&) const;
          glm::vec4 eye_to_clip    (glm::vec4 const&) const;
          glm::vec3 clip_to_ndc    (glm::vec4 const&) const;

        protected:
          
          explicit base();
          
          using fragment_list_type = rasterizer::base::fragment_list_type;
          using index_list_type    = primitive::base::index_list_type;
          using vertex_list_type   = primitive::base::vertex_list_type;
          
          template <primitive::topology>
            fragment_list_type raster(index_list_type const&  /* indices   */,
                                      vertex_list_type const& /* vertices  */);
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

        template <> HUGH_RENDER_SOFTWARE_EXPORT base::fragment_list_type
        base::raster<primitive::topology::point_list>    (index_list_type const&,
                                                          vertex_list_type const&);
        template <> HUGH_RENDER_SOFTWARE_EXPORT base::fragment_list_type
        base::raster<primitive::topology::line_list>     (index_list_type const&,
                                                          vertex_list_type const&);
        template <> HUGH_RENDER_SOFTWARE_EXPORT base::fragment_list_type
        base::raster<primitive::topology::line_strip>    (index_list_type const&,
                                                          vertex_list_type const&);
        template <> HUGH_RENDER_SOFTWARE_EXPORT base::fragment_list_type
        base::raster<primitive::topology::triangle_list> (index_list_type const&,
                                                          vertex_list_type const&);
        template <> HUGH_RENDER_SOFTWARE_EXPORT base::fragment_list_type
        base::raster<primitive::topology::triangle_strip>(index_list_type const&,
                                                          vertex_list_type const&);
        
        HUGH_RENDER_SOFTWARE_EXPORT std::ostream&
        operator<<(std::ostream&, base::statistics const&);
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_BASE_HPP)
