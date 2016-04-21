// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/buffer/base.hpp                                            */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_BUFFER_BASE_HPP)

#define HUGH_RENDER_SOFTWARE_BUFFER_BASE_HPP

// includes, system

#include <glm/glm.hpp> // glm::*

// includes, project

#include <hugh/field/container.hpp>
#include <hugh/field/value/single.hpp>
#include <hugh/render/software/fragment.hpp>
#include <hugh/scene/object/camera/viewport.hpp>
#include <hugh/support/refcounted.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace buffer {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT base : public field::container,
                                                 public support::refcounted<base> {

        public:

          using viewport_type = scene::object::camera::viewport;

          field::value::single<viewport_type> viewport; //<
          
          virtual ~base();

          //virtual void clear ()                =0;
          virtual bool update(fragment const&) =0;
          
        protected:
          
          explicit base(viewport_type const&);
    
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace buffer {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_BUFFER_BASE_HPP)
