// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/pipeline_fixed_shared.hpp                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_TEST_PIPELINE_FIXED_SHARED_HPP)

#define HUGH_RENDER_SOFTWARE_TEST_PIPELINE_FIXED_SHARED_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/scene/object/camera/viewport.hpp>

namespace hugh {

  namespace render {

    namespace software {

      namespace pipeline {

        namespace fixed {

          class base;
          
        } // namespace fixed {
        
      } // namespace pipeline {
      
      namespace test {
        
        // types, exported (class, enum, struct, union, typedef)

        // variables, exported (extern)

        using viewport_type = hugh::scene::object::camera::viewport;

        extern viewport_type const default_viewport;
        
        // functions, inlined (inline)

        // functions, exported (extern)
        
        void process_point_list    (pipeline::fixed::base&);
        void process_line_list     (pipeline::fixed::base&);
        void process_line_strip    (pipeline::fixed::base&);
        void process_triangle_list (pipeline::fixed::base&);
        void process_triangle_strip(pipeline::fixed::base&);
          
      } // namespace test {

    } // namespace software {
  
  } // namespace render {
      
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_TEST_PIPELINE_FIXED_SHARED_HPP)
