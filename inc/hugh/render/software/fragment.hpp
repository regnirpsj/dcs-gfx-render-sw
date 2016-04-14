// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/fragment.hpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_FRAGMENT_HPP)

#define HUGH_RENDER_SOFTWARE_FRAGMENT_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/attribute.hpp>
#include <hugh/render/software/export.h>
#include <hugh/support/printable.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      // types, exported (class, enum, struct, union, typedef)

      class HUGH_RENDER_SOFTWARE_EXPORT fragment : public support::printable {

      public:

        glm::uvec2      position;
        float           depth;
        attribute::list attributes;
        
        explicit fragment(glm::uvec2 const&, float, attribute::list const& = attribute::list());
        virtual ~fragment();
        
        virtual void print_on(std::ostream&) const;
        
      };
        
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_FRAGMENT_HPP)
