// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/point_list.hpp                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_POINT_LIST_HPP)

#define HUGH_RENDER_SOFTWARE_PRIMITIVE_POINT_LIST_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/render/software/primitive/base.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace primitive {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT point_list : public base {

        public:

          explicit point_list(vertex_list_type const& /* vertices */,
                              index_list_type const&  /* indices  */ = index_list_type());
          virtual ~point_list();
    
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_POINT_LIST_HPP)
