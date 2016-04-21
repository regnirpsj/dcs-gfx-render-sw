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

#include <hugh/render/software/buffer/color.hpp>
#include <hugh/render/software/buffer/depth.hpp>
#include <hugh/render/software/pipeline/fixed/opengl.hpp>
#include <hugh/render/software/rasterizer/simple.hpp>

// includes, project

#include <gtkmm_wrap/check_button_input.hpp>
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
    viewport_          (0, 0, 320, 240, 0, 1),
    pipeline_          (nullptr),
    win_color_         (nullptr),
    win_depth_         (nullptr)
{
  TRACE("window_control::window_control");

  {
    set_title             ("pipeline::fixed");
    set_default_size      (250, 600);
    set_border_width      (2);
    set_resizable         (true);
    set_reallocate_redraws(true);
  }
  
  using namespace hugh::render::software;
  
  {
    pipeline_.reset(new hugh::render::software::pipeline::fixed::opengl);
    
    pipeline_->rasterizer  = new rasterizer::simple(viewport_);
    pipeline_->colorbuffer = new buffer::color     (viewport_);
    pipeline_->depthbuffer = new buffer::depth     (viewport_);

    (*pipeline_->colorbuffer)->clear(glm::vec4(0,1,0,1));
    (*pipeline_->depthbuffer)->clear(glm::vec1(0.5));
    
    win_color_.reset(new window_buffer(get_title(), (*pipeline_->colorbuffer).get()));
    win_depth_.reset(new window_buffer(get_title(), (*pipeline_->depthbuffer).get()));
    
    win_depth_->set_visible(false);
  }

  {
    using namespace hugh::gtkmm;

    std::array<Gtk::Widget*, 2> const control_item_list = {
      {
        empty_label_in_framed_vbox("Viewport", "[x y w h dn df]"),
        empty_label_in_framed_vbox("Pipeline", "D3D/OGL"),
      }
    };

    std::array<Gtk::Widget*, 2> const stats_ppl_item_list = {
      {
        empty_label_in_framed_vbox("Vertices", ""),
        empty_label_in_framed_vbox("Fragments", ""),
      }
    };
    
    std::array<Gtk::Widget*, 1> const stats_item_list = {
      {
        pack_items_in_framed_hbox<2>("Pipeline", stats_ppl_item_list),
      }
    };

    std::array<Gtk::Widget*, 3> const output_buffer_item_list = {
      {
        Gtk::manage(new check_button_input<bool>
                    ("  Color",
                     [&]()       { return win_color_->get_visible(); },
                     [&](bool a) { bool r(win_color_->get_visible());
                                   win_color_->set_visible(a);
                                   return r; },
                     "Toggle color-buffer display.", true, true)),
        Gtk::manage(new check_button_input<bool>
                    ("  Depth",
                     [&]()       { return win_depth_->get_visible(); },
                     [&](bool a) { bool r(win_depth_->get_visible());
                                   win_depth_->set_visible(a);
                                   return r; },
                     "Toggle depth-buffer display.", true, true)),
        Gtk::manage(new check_button_input<bool>
                    ("Stencil",
                     [&]()       { return false; },
                     [&](bool)   { return false; },
                     "Toggle stencil-buffer display.", false, true)),
      }
    };
    
    std::array<Gtk::Widget*, 1> const output_item_list = {
      {
        pack_items_in_framed_vbox<3>("Buffer", output_buffer_item_list),
      }
    };
    
    std::array<Gtk::Widget*, 3> const top_level = {
      {
        pack_items_in_framed_vbox<2>("Control", control_item_list),
        pack_items_in_framed_vbox<1>("Stats",   stats_item_list),
        pack_items_in_framed_vbox<1>("Output",  output_item_list),
      }
    };

    add     (*pack_items_in_vbox<3>(top_level));
    show_all();
  }
}

/* virtual */
window_control::~window_control()
{
  TRACE("window_control::~window_control");
}
