// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/fixed/base.hpp                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_BASE_HPP)

#define HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_BASE_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/pipeline/base.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace pipeline {

        namespace fixed {
          
          // types, exported (class, enum, struct, union, typedef)

          class HUGH_RENDER_SOFTWARE_EXPORT base : public pipeline::base {

          public:

            explicit base();
            virtual ~base();

            virtual void process(primitive::base const&);          

          protected:

            vertex   transform(vertex const&)   const;
            fragment shade    (fragment const&) const;
          
          };
        
          // variables, exported (extern)

          // functions, inlined (inline)
  
          // functions, exported (extern)

        } // namespace fixed {
        
      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PIPELINE_FIXED_BASE_HPP)
