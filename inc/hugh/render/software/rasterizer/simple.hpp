// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/rasterizer/simple.hpp                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_RASTERIZER_SIMPLE_HPP)

#define HUGH_RENDER_SOFTWARE_RASTERIZER_SIMPLE_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/render/software/rasterizer/base.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace rasterizer {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT simple : public base {

        public:

          explicit simple(viewport_type const& = viewport_type());
          virtual ~simple();

          virtual fragment_list_type process(vertex const&) const;
          virtual fragment_list_type process(vertex const&, vertex const&) const;
          virtual fragment_list_type process(vertex const&, vertex const&, vertex const&) const;
          
    
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace rasterizer {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_RASTERIZER_SIMPLE_HPP)
