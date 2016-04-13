// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/triangles.hpp                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_TRIANGLES_HPP)

#define HUGH_RENDER_SOFTWARE_PRIMITIVE_TRIANGLES_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/render/software/primitive/base.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace primitive {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT triangles : public base {

        public:

          explicit triangles();
          virtual ~triangles();
    
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_TRIANGLES_HPP)
