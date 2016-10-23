// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/flexible/opengl.hpp                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_FLEXIBLE_OPENGL_HPP)

#define HUGH_RENDER_SOFTWARE_PIPELINE_FLEXIBLE_OPENGL_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/pipeline/flexible/base.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace pipeline {

        namespace flexible {
          
          // types, exported (class, enum, struct, union, typedef)

          class HUGH_RENDER_SOFTWARE_EXPORT opengl : public base {

          public:

            explicit opengl();
            virtual ~opengl();

            // exposing previously 'protected' methods
            using base::transform;
            using base::shade;

          protected:
            
            virtual glm::vec3 ndc_to_window(glm::vec3 const&) const;
          
          };        
        
          // variables, exported (extern)

          // functions, inlined (inline)
  
          // functions, exported (extern)

        } // namespace flexible {
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_FLEXIBLE_OPENGL_HPP)
