// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  pipeline_fixed/window_buffer.hpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_PIPELINE_FIXED_WINDOW_BUFFER_HPP)

#define HUGH_PIPELINE_FIXED_WINDOW_BUFFER_HPP

// includes, system

#include <boost/intrusive_ptr.hpp> // boost::intrusive_ptr<>

// includes, project

#include <gtkmm_wrap/window.hpp>
#include <hugh/render/software/buffer/base.hpp>

// types, exported (class, enum, struct, union, typedef)

class window_buffer : public hugh::gtkmm::window {

public:

  explicit window_buffer();
  virtual ~window_buffer();
  
private:

  boost::intrusive_ptr<hugh::render::software::buffer::base> buffer_;
  
};

// variables, exported (extern)

// functions, inlined (inline)
  
// functions, exported (extern)  

#endif // #if !defined(HUGH_PIPELINE_FIXED_WINDOW_BUFFER_HPP)
