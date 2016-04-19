// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/fixed.hpp                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_HPP)

#define HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/pipeline/base.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace pipeline {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT fixed : public base {

        public:

          explicit fixed();
          virtual ~fixed();

          virtual void process(primitive::base const&);          

        protected:

          vertex   transform(vertex const&)   const;
          fragment shade    (fragment const&) const;
          
        };

        class HUGH_RENDER_SOFTWARE_EXPORT d3d : public fixed {

        public:

          explicit d3d();
          virtual ~d3d();

          // exposing previously 'protected' methods
          using fixed::object_to_world;
          using fixed::world_to_eye;
          using fixed::eye_to_clip;;
          using fixed::clip_to_ndc;
          
          virtual glm::vec3 ndc_to_window(glm::vec3 const&) const;
          
        };
        
        class HUGH_RENDER_SOFTWARE_EXPORT opengl : public fixed {

        public:

          explicit opengl();
          virtual ~opengl();

          // exposing previously 'protected' methods
          using fixed::object_to_world;
          using fixed::world_to_eye;
          using fixed::eye_to_clip;;
          using fixed::clip_to_ndc;
          
          virtual glm::vec3 ndc_to_window(glm::vec3 const&) const;
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_HPP)
