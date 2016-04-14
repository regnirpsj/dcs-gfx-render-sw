// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/triangle_strip.hpp                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_TRIANGLE_STRIP_HPP)

#define HUGH_RENDER_SOFTWARE_PRIMITIVE_TRIANGLE_STRIP_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/render/software/primitive/base.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace primitive {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT triangle_strip : public base {

        public:

          explicit triangle_strip(vertex_list_type const& /* vertices */,
                                  index_list_type const&  /* indices  */ = index_list_type());
          virtual ~triangle_strip();
    
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_TRIANGLE_STRIP_HPP)
