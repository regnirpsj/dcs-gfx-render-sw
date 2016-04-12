// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive.hpp                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_HPP)

#define HUGH_RENDER_SOFTWARE_PRIMITIVE_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/render/software/export.h>

namespace hugh {

  namespace render {

    namespace software {
      
      // types, exported (class, enum, struct, union, typedef)

      class HUGH_RENDER_SOFTWARE_EXPORT primitive {

      public:

        explicit primitive();
        virtual ~primitive();
    
      };
        
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_HPP)
