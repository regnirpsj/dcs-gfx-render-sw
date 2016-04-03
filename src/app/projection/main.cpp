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

#include <boost/lexical_cast.hpp>
#include <cstdlib>                      // EXIT_SUCCESS
#include <glm/gtc/matrix_transform.hpp> // glm::frustum
#include <glm/gtx/io.hpp>               // glm::io::*
#include <iostream>                     // std::cout, std:endl
#include <regex>

// includes, project

#include <glm/gtx/utilities.hpp>
#include <hugh/platform/posix/application/base.hpp>
#include <hugh/scene/object/camera/frustum.hpp>
#include <hugh/support/io_utils.hpp>

#include <../common/pipeline.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

namespace glm {
  
  template <typename T, precision P = defaultp>
  void
  validate(boost::any& result, std::vector<std::string> const& values, tvec3<T,P>*, int)
  {
    TRACE("glm::validate(tvec3<" + hugh::support::demangle(typeid(T)) + "," +
          hugh::support::demangle(typeid(P)) + ">)");

    namespace bpo = boost::program_options;
    
#if 0
    {
      using hugh::support::ostream::operator<<;
      
      std::cout << "validate:" << values.size() << ':' << values << '\n';
    }
#endif
    
    if (1 != values.size()) {
      throw bpo::validation_error(bpo::validation_error::invalid_option_value);
    }

    static std::string const float1("([-+]?[0-9]*\\.?[0-9]+)");
    static std::string const float3(float1 + ",?" + float1 + ",?" + float1);
    static std::regex const  regex (float3, std::regex::extended);
    
    std::smatch match;
    bool const  found(std::regex_search(values.at(0), match, regex));

#if 0
    std::cout << (found ? "" : "!") << "found " << match.size() << " matches for '"
              << values.at(0) << "' w/ " << float3 << '\n';
#endif
    
    if (!found || (4 > match.size())) {
      throw bpo::validation_error(bpo::validation_error::invalid_option_value);
    }

#if 0
    for (unsigned i(0); i < match.size(); ++i) {
      std::cout << "m[" << i << "]:" << match[i] << ", "
                << "sm[" << i << ']' << std::ssub_match(match[i]).str() << '\n';
    }
#endif
    
    result = tvec3<T,P>(boost::lexical_cast<float>(std::ssub_match(match[1]).str()),
                        boost::lexical_cast<float>(std::ssub_match(match[2]).str()),
                        boost::lexical_cast<float>(std::ssub_match(match[3]).str()));
  }
  
} // namespace glm {

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  using namespace hugh::platform;
  
  class app : public posix::application::base {

    using inherited  = posix::application::base;
    using frustum_t  = hugh::scene::object::camera::frustum;
    using viewport_t = hugh::scene::object::camera::viewport;
    
  public:
    
    explicit app(application::command_line const& a)
      : inherited(a, !inherited::positionals),
        show_d3d_        (true),
        show_ogl_        (true),
        show_vk_         (true),
        frustum_         (-1.0, 1.0, -1.0, 1.0, 0.1, 100.0),
        viewport_        (0, 0, 100, 100, 0, 1),
        xform_model_     (),
        xform_view_      (),
        xform_projection_(glm::frustum(frustum_.left, frustum_.right,
                                       frustum_.bottom, frustum_.top,
                                       frustum_.near, frustum_.far)),
        position_        (0.0, 0.0, -0.125),
        normal_          (0.0, 1.0,  0.0)
    {
      TRACE("<unnamed>::app::app");

      namespace bpo = boost::program_options;
          
      bpo::options_description od("Application Options");

      od.add_options()
        ("directx,1",
         bpo::value<bool>(&show_d3d_)     ->default_value(show_d3d_),
         "Display DirectX 10+ pipeline");
      
      od.add_options()
        ("opengl,2",
         bpo::value<bool>(&show_ogl_)     ->default_value(show_ogl_),
         "Display OpenGL 4+ pipeline");
      
      od.add_options()
        ("vulkan,3",
         bpo::value<bool>(&show_vk_)      ->default_value(show_vk_),
         "Display Vulkan pipeline");

      od.add_options()
        ("normal,n",
         bpo::value<glm::vec3>(&normal_)  ->default_value(normal_)->multitoken(),
         "Input normal (format:x,y,z)");

      od.add_options()
        ("position,p",
         bpo::value<glm::vec3>(&position_)->default_value(position_)->multitoken(),
         "Input position (format:x,y,z)");
      
      command_line_.descriptions.add(od);
    }

    virtual signed run()
    {
      TRACE("<unnamed>::app::run");      

      std::cout << glm::io::precision(2) << glm::io::width(1 + 2 + 1 + 2);
      
      normal_ = glm::normalize(normal_);
      
      if (show_d3d_) {
        pipeline::d3d const d3d(xform_model_,
                                xform_view_,
                                glm::convert::opengl_to_d3d * xform_projection_,
                                viewport_);

        if (1 < verbose_level_) {
          std::cout << "d3d:" << d3d << std::endl;
        }
      
        std::cout << "d3d(p):" << d3d.transform(position_, true)  << std::endl;
        std::cout << "d3d(n):" << d3d.transform(normal_,   false) << std::endl;
      }

      if (show_ogl_) {
        pipeline::opengl const ogl(xform_model_, xform_view_, xform_projection_, viewport_);

        if (1 < verbose_level_) {
          std::cout << "ogl:" << ogl << std::endl;
        }
      
        std::cout << "ogl(p):" << ogl.transform(position_, true)  << std::endl;
        std::cout << "ogl(n):" << ogl.transform(normal_,   false) << std::endl;
      }

#if 0
      if (show_vk_) {
        pipeline::opengl const vk(xform_model_, xform_view_, xform_projection_, viewport_);

        if (1 < verbose_level_) {
          std::cout << "vk:" << vk << std::endl;
        }
      
        std::cout << "vk(p):" << vk.transform(position_, true)  << std::endl;
        std::cout << "vk(n):" << vk.transform(normal_,   false) << std::endl;
      }
#endif
      
      return EXIT_SUCCESS;
    }

  private:

    bool       show_d3d_;
    bool       show_ogl_;
    bool       show_vk_;
    frustum_t  frustum_;
    viewport_t viewport_;
    glm::mat4  xform_model_;
    glm::mat4  xform_view_;
    glm::mat4  xform_projection_;
    glm::vec3  position_;
    glm::vec3  normal_;
    
  };
  
  // variables, internal
  
  // functions, internal

} // namespace {

int
main(int argc, char const* argv[])
{
  TRACE("main");

  using namespace hugh::platform::application;
  
  return execute<app>(command_line(argc, argv), std::nothrow);
}
