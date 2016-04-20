// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  pipeline_fixed/window_control.hpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_PIPELINE_FIXED_WINDOW_CONTROL_HPP)

#define HUGH_PIPELINE_FIXED_WINDOW_CONTROL_HPP

// includes, system

#include <memory> // std::unique_ptr<>

// includes, project

#include <gtkmm_wrap/window.hpp>
#include <window_buffer.hpp>

// types, exported (class, enum, struct, union, typedef)

class window_control : public hugh::gtkmm::window {

public:

  explicit window_control();
  virtual ~window_control();
  
private:
  
  Gtk::VBox                      vbox_;

  std::unique_ptr<window_buffer> win_cbuf_;
  std::unique_ptr<window_buffer> win_dbuf_;

  void on_btn_cbuf_clicked();
  void on_btn_dbuf_clicked();
  
};

// variables, exported (extern)

// functions, inlined (inline)
  
// functions, exported (extern)  

#endif // #if !defined(HUGH_PIPELINE_FIXED_WINDOW_CONTROL_HPP)
