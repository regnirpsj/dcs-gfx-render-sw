// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/fixed/direct3d.hpp                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_DIRECT3D_HPP)

#define HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_DIRECT3D_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/pipeline/fixed/base.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace pipeline {

        namespace fixed {
          
          // types, exported (class, enum, struct, union, typedef)

          class HUGH_RENDER_SOFTWARE_EXPORT direct3d : public base {

          public:

            explicit direct3d();
            virtual ~direct3d();

            // exposing previously 'protected' methods
            using base::transform;
            using base::shade;

          protected:
            
            virtual glm::vec3 ndc_to_window(glm::vec3 const&) const;
          
          };        
        
          // variables, exported (extern)

          // functions, inlined (inline)
  
          // functions, exported (extern)

        } // namespace fixed {
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_DIRECT3D_HPP)
