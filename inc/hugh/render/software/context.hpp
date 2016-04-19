// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/context.hpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_CONTEXT_HPP)

#define HUGH_RENDER_SOFTWARE_CONTEXT_HPP

// includes, system

#include <boost/intrusive_ptr.hpp> // boost::intrusive_ptr<>
#include <glm/glm.hpp>             // glm::*

// includes, project

#include <hugh/field/container.hpp>
#include <hugh/field/value/single.hpp>
#include <hugh/render/software/buffer/color.hpp>
#include <hugh/render/software/buffer/depth.hpp>
#include <hugh/render/software/export.h>
#include <hugh/render/software/pipeline/base.hpp>
#include <hugh/render/software/rasterizer/base.hpp>
#include <hugh/scene/object/camera/viewport.hpp>

namespace hugh {

  namespace render {

    namespace software {
        
      // types, exported (class, enum, struct, union, typedef)

      class HUGH_RENDER_SOFTWARE_EXPORT context : public field::container {

      public:

        using viewport_type = scene::object::camera::viewport;
        
        field::value::single<viewport_type> viewport; //< [ x, y, w, h, n, f ]
        
        explicit context(pipeline::base*, viewport_type const& = viewport_type());
        virtual ~context();

        virtual void clear ();
        virtual void submit();
        virtual void flush ();

      protected:

        using color_buffer_type = boost::intrusive_ptr<buffer::color>;
        using depth_buffer_type = boost::intrusive_ptr<buffer::depth>;
        using pipeline_type     = boost::intrusive_ptr<pipeline::base>;
        using rasterizer_type   = boost::intrusive_ptr<rasterizer::base>;
        
        field::value::single<color_buffer_type> colorbuffer; //<
        field::value::single<depth_buffer_type> depthbuffer; //<
        field::value::single<rasterizer_type>   rasterizer;  //<
        field::value::single<pipeline_type>     pipeline;    //<

        virtual void do_evaluate();
        virtual void do_changed (field::base&);
        
      };
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_CONTEXT_HPP)
