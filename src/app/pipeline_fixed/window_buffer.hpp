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
#include <hugh/render/software/buffer/color.hpp>
#include <hugh/render/software/buffer/depth.hpp>

// types, exported (class, enum, struct, union, typedef)

class window_buffer : public hugh::gtkmm::window {

public:

  using cbuffer_type = hugh::render::software::buffer::color;
  using dbuffer_type = hugh::render::software::buffer::depth;
  
  explicit window_buffer(std::string const&, cbuffer_type*);
  explicit window_buffer(std::string const&, dbuffer_type*);
  virtual ~window_buffer();
  
private:

  using buffer_type = hugh::render::software::buffer::base;
  
  enum class type { color, depth };
  
  boost::intrusive_ptr<buffer_type> buffer_;
  type const                        type_;

  explicit window_buffer(std::string const&, buffer_type*, type);

  virtual bool on_draw(::Cairo::RefPtr<::Cairo::Context> const&);
  
};

// variables, exported (extern)

// functions, inlined (inline)
  
// functions, exported (extern)  

#endif // #if !defined(HUGH_PIPELINE_FIXED_WINDOW_BUFFER_HPP)
