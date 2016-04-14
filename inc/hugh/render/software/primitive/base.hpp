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

#include <iosfwd> // std::ostream (fwd decl)
#include <vector> // std::vector<>

// includes, project

#include <hugh/render/software/export.h>
#include <hugh/render/software/vertex.hpp>
#include <hugh/support/printable.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace primitive {
        
        // types, exported (class, enum, struct, union, typedef)

        enum class topology { point_list, line_list, line_strip, triangle_list, triangle_strip, };
        
        class HUGH_RENDER_SOFTWARE_EXPORT base : public support::printable {

        public:

          using vertex_list_type = std::vector<vertex>;
          using index_list_type  = std::vector<unsigned>;
          
          primitive::topology const  topology;
          vertex_list_type const     vertices;
          index_list_type const      indices;
          
          virtual ~base();

          virtual void print_on(std::ostream&) const;

        protected:

          explicit base(primitive::topology);
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

        HUGH_RENDER_SOFTWARE_EXPORT std::ostream& operator<<(std::ostream&, topology const&);
        
      } // namespace primitive_base {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_PRIMITIVE_BASE_HPP)
