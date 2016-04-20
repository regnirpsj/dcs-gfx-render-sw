// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  pipeline_fixed/window_control.cpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "window_control.hpp"

// includes, system

//#include <>

// includes, project

#include <gtkmm_wrap/utilities.hpp>

#define HUGH_USE_TRACE
//#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

  
} // namespace {

// variables, exported

// functions, exported

/* explicit */
window_control::window_control()
  : hugh::gtkmm::window(),
    vbox_              (),
    win_cbuf_          (nullptr),
    win_dbuf_          (nullptr)
{
  TRACE("window_control::window_control");

  set_border_width      (2);
  set_resizable         (true);
  set_reallocate_redraws(true);
      
  add(vbox_);

  {
    Gtk::Frame* frame0(Gtk::manage(new Gtk::Frame("Pipeline")));

    vbox_.add(*frame0);
  }

  {
    Gtk::Frame* frame0(Gtk::manage(new Gtk::Frame("Statistics")));

    vbox_.add(*frame0);
  }
  
  {
    Gtk::Frame* frame0(Gtk::manage(new Gtk::Frame("Controls")));

    {
      Gtk::Frame* frame1(Gtk::manage(new Gtk::Frame("Buffer")));

      {
        Gtk::Box* hbox(Gtk::manage(new Gtk::HBox));

        {
          Gtk::CheckButton* btn(Gtk::manage(new Gtk::CheckButton("Color")));

          btn->signal_clicked()
            .connect(sigc::mem_fun(*this, &window_control::on_btn_cbuf_clicked));
            
          hbox->add(*btn);
        }

        {
          Gtk::CheckButton* btn(Gtk::manage(new Gtk::CheckButton("Depth")));

          btn->signal_clicked()
            .connect(sigc::mem_fun(*this, &window_control::on_btn_dbuf_clicked));
          
          hbox->add(*btn);
        }
        
        frame1->add(*hbox);
      }

      frame0->add(*frame1);
    }
    
    vbox_.add(*frame0);
  }
  
  show_all();
}

/* virtual */
window_control::~window_control()
{
  TRACE("window_control::~window_control");
}

void
window_control::on_btn_cbuf_clicked()
{
  TRACE("window_control::on_btn_cbuf_clicked");

  if (!win_cbuf_) {
    win_cbuf_ .reset(new window_buffer);
    win_cbuf_->show ();
  } else {
    win_cbuf_.reset (nullptr);
  }
}

void
window_control::on_btn_dbuf_clicked()
{
  TRACE("window_control::on_btn_dbuf_clicked");
  
  if (!win_dbuf_) {
    win_dbuf_ .reset(new window_buffer);
    win_dbuf_->show ();
  } else {
    win_dbuf_.reset (nullptr);
  }
}
