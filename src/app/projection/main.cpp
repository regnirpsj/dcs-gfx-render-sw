// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  projection/main.cpp                                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <cstdlib>                      // EXIT_SUCCESS
#include <glm/gtc/matrix_transform.hpp> // glm::frustum
#include <glm/gtx/io.hpp>               // glm::io::*
#include <iostream>                     // std::cout, std:endl

// includes, project

#include <glm/gtx/utilities.hpp>
#include <hugh/platform/posix/application/base.hpp>
#include <hugh/scene/object/camera/frustum.hpp>

#include <../common/pipeline.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  using namespace hugh::platform;
  
  class app : public posix::application::base {

    using inherited = posix::application::base;

  public:

    explicit app(application::command_line const& a)
      : inherited(a)
    {
      TRACE("<unnamed>::app::app");
    }

    virtual signed run()
    {
      TRACE("<unnamed>::app::run");
      
      using frustum = hugh::scene::object::camera::frustum;

      frustum const                  f(-1.0, 1.0, -1.0, 1.0, 0.1, 100.0);
      glm::mat4 const                xform_proj(glm::frustum(f.left, f.right,
                                                             f.bottom, f.top,
                                                             f.near, f.far));
      pipeline::base::viewport const vport(0, 0, 100, 100, 0, 1);
      
      glm::vec3 const p(0.0, 0.0, -0.125);
      glm::vec3 const n(0.0, 1.0,  0.0);
      
      std::cout << glm::io::precision(2) << glm::io::width(1 + 2 + 1 + 2);
      
      pipeline::d3d const d3d(glm::mat4(),
                              glm::mat4(),
                              glm::convert::opengl_to_d3d * xform_proj,
                              vport);

      //std::cout << "d3d:"    << d3d                     << std::endl;
      std::cout << "d3d(p):" << d3d.transform(p, true)  << std::endl;
      std::cout << "d3d(n):" << d3d.transform(n, false) << std::endl;

      pipeline::opengl const ogl(glm::mat4(),
                                 glm::mat4(),
                                 xform_proj,
                                 vport);
      
      //std::cout << "ogl:"    << ogl                     << std::endl;
      std::cout << "ogl(p):" << ogl.transform(p, true)  << std::endl;
      std::cout << "ogl(n):" << ogl.transform(n, false) << std::endl;
      
      return EXIT_SUCCESS;
    }
    
  };
  
  // variables, internal
  
  // functions, internal

} // namespace {

int
main(int argc, char const* argv[])
{
  TRACE("main");

  using namespace hugh::platform;
  
  return application::execute<app>(application::command_line(argc, argv));
}
