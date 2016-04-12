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

// #include <>

// includes, project

#include <hugh/render/software/export.h>
#include <hugh/support/refcounted.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace buffer {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT base : public support::refcounted<base> {

        public:
          
          virtual ~base();
          
        protected:

          explicit base();
    
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace buffer {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_BUFFER_BASE_HPP)
