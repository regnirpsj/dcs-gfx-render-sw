// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/base.hpp                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_BASE_HPP)

#define HUGH_RENDER_SOFTWARE_PRIMITIVE_BASE_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/render/software/export.h>
#include <hugh/support/printable.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace primitive {
        
        // types, exported (class, enum, struct, union, typedef)

        enum class type { points, lines, triangles, };
        
        class HUGH_RENDER_SOFTWARE_EXPORT base : public support::printable {

        public:

          primitive::type const type;
          
          virtual ~base();

          virtual void print_on(std::ostream&) const;

        protected:

          explicit base(primitive::type);
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace primitive_base {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_BASE_HPP)
