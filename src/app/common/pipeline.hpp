// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  common/pipeline.hpp                                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_COMMON_PIPELINE_HPP)

#define HUGH_COMMON_PIPELINE_HPP

// includes, system

#include <glm/glm.hpp> // glm::*
#include <iosfwd>      // std::ostream (fwd decl)

// includes, project

#include <hugh/scene/object/camera/viewport.hpp>
#include <hugh/support/printable.hpp>

namespace pipeline {
  
  // types, exported (class, enum, struct, union, typedef)

  struct result {

  public:

    glm::vec3 const world;
    glm::vec4 const homogeneous;
    glm::vec4 const clip;
    glm::vec3 const ndc;
    glm::vec3 const window;

    explicit result(glm::vec3 const& /* world       */,
                    glm::vec4 const& /* homogeneous */,
                    glm::vec4 const& /* clip        */,
                    glm::vec3 const& /* ndc         */,
                    glm::vec3 const& /* window      */);
    
  };
  
  class base : public hugh::support::printable {

  public:

    using viewport = hugh::scene::object::camera::viewport;
    
    virtual ~base();

    result transform(glm::vec3 const& /* point/normal */, bool /* point? */) const;

    virtual void print_on(std::ostream&) const;
    
  protected:

    glm::mat4 const xform_model_;
    glm::mat4 const xform_view_;
    glm::mat4 const xform_proj_;
    viewport const  viewport_;
    
    explicit base(glm::mat4 const& /* model xform      */ = glm::mat4(),
                  glm::mat4 const& /* view xform       */ = glm::mat4(),
                  glm::mat4 const& /* projection xform */ = glm::mat4(),
                  viewport const&  /* viewport         */ = viewport());

    glm::vec4 eye_to_clip(glm::vec4 const& /* point/normal */) const;
    glm::vec3 clip_to_ndc(glm::vec4 const& /* point/normal */) const;

    virtual glm::vec3 ndc_to_wc(glm::vec3 const& /* point/normal */) const =0;
    
  };

  class d3d : public base {

  public:

    explicit d3d(glm::mat4 const& /* model xform      */ = glm::mat4(),
                 glm::mat4 const& /* view xform       */ = glm::mat4(),
                 glm::mat4 const& /* projection xform */ = glm::mat4(),
                 viewport const&  /* viewport         */ = viewport());
    
  protected:

    virtual glm::vec3 ndc_to_wc(glm::vec3 const& /* point/normal */) const;
    
  };
  
  class opengl : public base {

  public:

    explicit opengl(glm::mat4 const& /* model xform      */ = glm::mat4(),
                    glm::mat4 const& /* view xform       */ = glm::mat4(),
                    glm::mat4 const& /* projection xform */ = glm::mat4(),
                    viewport const&  /* viewport         */ = viewport());
    
  protected:

    virtual glm::vec3 ndc_to_wc(glm::vec3 const& /* point/normal */) const;
    
  };
  
  // variables, exported (extern)

  // functions, inlined (inline)
  
  // functions, exported (extern)

  std::ostream& operator<<(std::ostream&, result const&);
  
} // namespace pipeline {

#endif // #if !defined(HUGH_COMMON_PIPELINE_HPP)
