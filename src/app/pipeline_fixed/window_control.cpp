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
#include <hugh/render/software/pipelines.hpp>
#include <hugh/render/software/primitives.hpp>
#include <hugh/render/software/rasterizer/simple.hpp>

// includes, project

#include <gtkmm_wrap/check_button_input.hpp>
#include <gtkmm_wrap/radio_button_input.hpp>
#include <gtkmm_wrap/utilities.hpp>

#define HUGH_USE_TRACE
//#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  enum pipeline_enum { direct3d, opengl, };
  
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
    pipeline_.reset(new hugh::render::software::pipeline::fixed::direct3d);
    
    pipeline_->rasterizer  = new rasterizer::simple(viewport_);
    pipeline_->colorbuffer = new buffer::color     (viewport_);
    pipeline_->depthbuffer = new buffer::depth     (viewport_);

    // (*pipeline_->colorbuffer)->clear_value = glm::vec4(.1, .1, .1, .0);
      
    win_color_.reset(new window_buffer(get_title(), (*pipeline_->colorbuffer).get()));
    win_depth_.reset(new window_buffer(get_title(), (*pipeline_->depthbuffer).get()));
    
    win_depth_->set_visible(false);
  }

  {
    using namespace hugh::gtkmm;

    std::array<std::string, 2> const pipeline_enum_list = {
      { "Direct3D", "OpenGL", }
    };

    std::array<Gtk::Widget*, 1> const control_pipeline_item_list = {
      {
        Gtk::manage(new vradio_button_input<pipeline_enum>
                    ("",
                     [&](/*            */){
                      using namespace hugh::render::software::pipeline;
                      
                      return ((dynamic_cast<fixed::opengl*>(pipeline_.get()))
                              ? pipeline_enum::opengl
                              : pipeline_enum::direct3d);
                     },
                     [&](pipeline_enum a) {
                       using namespace hugh::render::software::pipeline;
                       
                       pipeline_enum const result((dynamic_cast<fixed::opengl*>(pipeline_.get()))
                                                  ? pipeline_enum::opengl
                                                  : pipeline_enum::direct3d);

                       fixed::base* ppl(nullptr);
                       
                       switch (a) {
                       case pipeline_enum::opengl:   ppl = new fixed::opengl;   break;
                       case pipeline_enum::direct3d: ppl = new fixed::direct3d; break;
                       }

                       ppl->rasterizer .set(pipeline_->rasterizer .get());
                       ppl->colorbuffer.set(pipeline_->colorbuffer.get());
                       ppl->depthbuffer.set(pipeline_->depthbuffer.get());

                       pipeline_.reset(ppl);
                       render();
                       
                       return result;
                     },
                     "Pipeline type.",
                     std::vector<std::string>(pipeline_enum_list.begin(),
                                              pipeline_enum_list.end()),
                     true, true)),
      }
    };
    
    std::array<Gtk::Widget*, 2> const control_item_list = {
      {
        empty_label_in_framed_vbox("Viewport", "[x y w h dn df]"),
        pack_items_in_framed_vbox<1>("Pipeline", control_pipeline_item_list),
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

  render();
}

/* virtual */
window_control::~window_control()
{
  TRACE("window_control::~window_control");
}

void
window_control::render()
{
  TRACE("window_control::render");

  using namespace hugh::render::software;
  
  const_cast<pipeline::base::statistics&>(*pipeline_->stats).reset();
  
  (*pipeline_->colorbuffer)->clear();
  (*pipeline_->depthbuffer)->clear();

  attribute::list const attr0({ { attribute::type::color, glm::vec4(1,1,1,1) } });
  attribute::list const attr1({ { attribute::type::color, glm::vec4(1,0,0,1) } });
  attribute::list const attr2({ { attribute::type::color, glm::vec4(0,1,0,1) } });
  attribute::list const attr3({ { attribute::type::color, glm::vec4(0,0,1,1) } });

  {
    auto const&     vp    (*(*pipeline_->rasterizer)->viewport);
    glm::vec2 const offset(.75, .75); //(vp.width-vp.x) / 100.0f, (vp.height-vp.y) / 100.0f);
    std::array<vertex const, 4> const vertices = {
      {
        vertex(glm::vec3(              0,               0, 0.25), attr0),
        vertex(glm::vec3(vp.x + offset.x, vp.y + offset.y, 0.35), attr1),
        vertex(glm::vec3(vp.x - offset.x, vp.y + offset.y, 0.45), attr2),
        vertex(glm::vec3(vp.x + offset.x, vp.y - offset.y, 0.55), attr3),
      }
    };

    using point_list  = primitive::point_list;
    using vertex_list = point_list::vertex_list_type;
    
    pipeline_->process(point_list(vertex_list(vertices.begin(), vertices.end())));
  }

  {
    auto const&     vp    (*(*pipeline_->rasterizer)->viewport);
    glm::vec2 const offset(.5, .5); //(vp.width-vp.x) / 100.0f, (vp.height-vp.y) / 100.0f);
    std::array<vertex const, 4> const vertices = {
      {
        vertex(glm::vec3(vp.x - offset.x, vp.y - offset.y, 0.35), attr1),
        vertex(glm::vec3(vp.x + offset.x, vp.y + offset.y, 0.45), attr3),
        vertex(glm::vec3(vp.x - offset.x, vp.y + offset.y, 0.45), attr3),
        vertex(glm::vec3(vp.x + offset.x, vp.y - offset.y, 0.35), attr1),
      }
    };

    using line_list  = primitive::line_list;
    using vertex_list = line_list::vertex_list_type;
    
    pipeline_->process(line_list(vertex_list(vertices.begin(), vertices.end())));
  }

  {
    auto const&     vp    (*(*pipeline_->rasterizer)->viewport);
    glm::vec2 const offset(.25, .25); //(vp.width-vp.x) / 100.0f, (vp.height-vp.y) / 100.0f);
    
    std::array<vertex const, 6> const vertices = {
      {
        // ccw
        vertex(glm::vec3(vp.x - offset.x, vp.y - offset.y, 0.45), attr1),
        vertex(glm::vec3(vp.x + offset.x, vp.y - offset.y, 0.55), attr2),
        vertex(glm::vec3(vp.x - offset.x, vp.y + offset.y, 0.65), attr3),
        // cw
        vertex(glm::vec3(vp.x - offset.x, vp.y - offset.y, 0.45), attr1),
        vertex(glm::vec3(vp.x - offset.x, vp.y + offset.y, 0.55), attr2),
        vertex(glm::vec3(vp.x + offset.x, vp.y - offset.y, 0.65), attr3),
      }
    };

    using triangle_list = primitive::triangle_list;
    using vertex_list   = triangle_list::vertex_list_type;
    
    pipeline_->process(triangle_list(vertex_list(vertices.begin(), vertices.end())));
  }
  
  win_color_->queue_draw();
  win_depth_->queue_draw();
  /*       */ queue_draw();
}
