// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/lines.hpp                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_LINES_HPP)

#define HUGH_RENDER_SOFTWARE_PRIMITIVE_LINES_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/render/software/primitive/base.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace primitive {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT lines : public base {

        public:

          explicit lines();
          virtual ~lines();

        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_LINES_HPP)
