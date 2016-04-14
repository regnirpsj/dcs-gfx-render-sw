// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/rasterizer/base.hpp                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_RASTERIZER_BASE_HPP)

#define HUGH_RENDER_SOFTWARE_RASTERIZER_BASE_HPP

// includes, system

#include <vector> // vector<>

// includes, project

#include <hugh/field/container.hpp>
#include <hugh/field/value/multi.hpp>
#include <hugh/field/value/single.hpp>
#include <hugh/render/software/export.h>
#include <hugh/render/software/fragment.hpp>
#include <hugh/render/software/line.hpp>
#include <hugh/render/software/triangle.hpp>
#include <hugh/scene/object/camera/viewport.hpp>
#include <hugh/support/refcounted.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace rasterizer {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT base : public field::container,
                                                 public support::refcounted<base> {

        public:

          using fragment_list_type = std::vector<fragment>;
          using viewport_type      = scene::object::camera::viewport;

          field::value::single<viewport_type> viewport;
          
          virtual ~base();

          virtual fragment_list_type process(vertex const&) const   =0;
          virtual fragment_list_type process(line const&) const     =0;
          virtual fragment_list_type process(triangle const&) const =0;
          
        protected:

          explicit base(viewport_type const& = viewport_type());
    
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace rasterizer {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_RASTERIZER_BASE_HPP)
