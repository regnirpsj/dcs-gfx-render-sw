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
#include <gtkmm_wrap/text_output.hpp>
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
    // viewport_          (0, 0, 80, 60, 0, 1),
    // viewport_          (0, 0, 320, 240, 0, 1),
    viewport_          (0, 0, 640, 480, 0, 1),
    // viewport_          (0, 0, 1200, 900, 0, 1),
    pipeline_          (nullptr),
    win_color_         (nullptr),
    win_depth_         (nullptr)
{
  TRACE("window_control::window_control");

  {
    set_title             ("pipeline::fixed");
    set_default_size      (500, 700);
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

    static unsigned const stats_number_width(8);
    
    std::array<Gtk::Widget*, 1> const stats_vertex_item_list = {
      {
        Gtk::manage(new text_output<std::string>
                    ("  Transformed:",
                     [&](){ return std::to_string((*pipeline_->stats).vertices.transformed); },
                     "Number of transformed vertices.", stats_number_width)),
      }
    };
    
    std::array<Gtk::Widget*, 5> const stats_fragment_item_list = {
      {
        Gtk::manage(new text_output<std::string>
                    ("      Created:",
                     [&](){ return std::to_string((*pipeline_->stats).fragments.created); },
                     "Number of created fragments.", stats_number_width)),
        Gtk::manage(new text_output<std::string>
                    ("     Z-Culled:",
                     [&](){ return std::to_string((*pipeline_->stats).fragments.zculled); },
                     "Number of z-culled fragments.", stats_number_width)),
        Gtk::manage(new text_output<std::string>
                    ("       Shaded:",
                     [&](){ return std::to_string((*pipeline_->stats).fragments.shaded); },
                     "Number of shaded fragments.", stats_number_width)),
        Gtk::manage(new text_output<std::string>
                    ("Z-Test Failed:",
                     [&](){ return std::to_string((*pipeline_->stats).fragments.ztestfailed); },
                     "Number of fragments where z-test failed.", stats_number_width)),
        Gtk::manage(new text_output<std::string>
                    ("      Updated:",
                     [&](){ return std::to_string((*pipeline_->stats).fragments.updated); },
                     "Number of fragments written to the frame buffer.", stats_number_width)),
      }
    };

    std::array<Gtk::Widget*, 2> const stats_pipeline_item_list = {
      {
        pack_items_in_framed_vbox<1>("Vertices",  stats_vertex_item_list),
        pack_items_in_framed_vbox<5>("Fragments", stats_fragment_item_list),
      }
    };
    
    std::array<Gtk::Widget*, 3> const stats_rasterizer_item_list = {
      {
        Gtk::manage(new text_output<std::string>
                    ("Points:",
                     [&](){ return std::to_string((*(*pipeline_->rasterizer)->stats).points); },
                     "Number of rasterized points.", stats_number_width)),
        Gtk::manage(new text_output<std::string>
                    ("Lines:",
                     [&](){ return std::to_string((*(*pipeline_->rasterizer)->stats).lines); },
                     "Number of rasterized lines.", stats_number_width)),
        Gtk::manage(new text_output<std::string>
                    ("Triangles:",
                     [&](){ return std::to_string((*(*pipeline_->rasterizer)->stats).triangles); },
                     "Number of rasterized triangles.", stats_number_width)),
      }
    };
    
    std::array<Gtk::Widget*, 2> const stats_item_list = {
      {
        pack_items_in_framed_hbox<2>("Pipeline",   stats_pipeline_item_list),
        pack_items_in_framed_hbox<3>("Rasterizer", stats_rasterizer_item_list),
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
        pack_items_in_framed_vbox<2>("Stats",   stats_item_list),
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

  const_cast<rasterizer::base::statistics&>(*(*pipeline_->rasterizer)->stats).reset();
  const_cast<pipeline::base::statistics&>(*pipeline_->stats).reset();
  
  (*pipeline_->colorbuffer)->clear();
  (*pipeline_->depthbuffer)->clear();

  static attribute::list const attr0({ { attribute::type::color, glm::vec4(1,1,1,0) } });
  static attribute::list const attr1({ { attribute::type::color, glm::vec4(1,0,0,0) } });
  static attribute::list const attr2({ { attribute::type::color, glm::vec4(0,1,0,0) } });
  static attribute::list const attr3({ { attribute::type::color, glm::vec4(0,0,1,0) } });
  static attribute::list const attr4({ { attribute::type::color, glm::vec4(1,1,0,0) } });
  static attribute::list const attr5({ { attribute::type::color, glm::vec4(1,0,1,0) } });
  static attribute::list const attr6({ { attribute::type::color, glm::vec4(0,1,1,0) } });

#if 1
  {
    static std::array<glm::vec3 const, 9> const p = {
      {
        {  .0,  .0, .0078 }, // 0:  0  0
        {  .9,  .0, .0078 }, // 1: +x  0
        {  .9,  .9, .0078 }, // 2: +x +y
        {  .0,  .9, .0078 }, // 3:  0 +y
        { -.9,  .9, .0078 }, // 4: -x +y
        { -.9,  .0, .0078 }, // 5: -x  0
        { -.9, -.9, .0078 }, // 6: -x -y
        {  .0, -.9, .0078 }, // 7:  0 -y
        {  .9, -.9, .0078 }, // 8: +x -y
      }
    };
    
    static std::array<vertex const, 9> const vertices = {
      {
        vertex(p[0], attr0),
        vertex(p[1], attr1),
        vertex(p[2], attr1),
        vertex(p[3], attr2),
        vertex(p[4], attr2),
        vertex(p[5], attr3),
        vertex(p[6], attr3),
        vertex(p[7], attr4),
        vertex(p[8], attr4),
      }
    };

    using point_list  = primitive::point_list;
    using vertex_list = point_list::vertex_list_type;
    
    pipeline_->process(point_list(vertex_list(vertices.begin(), vertices.end())));
  }
#endif
  
#if 1
  {
    static std::array<glm::vec3 const, 9> const p = {
      {
        {  .0,  .0, .5 }, // 0:  0  0
        {  .5,  .0, .5 }, // 1: +x  0
        {  .5,  .5, .5 }, // 2: +x +y
        {  .0,  .5, .5 }, // 3:  0 +y
        { -.5,  .5, .5 }, // 4: -x +y
        { -.5,  .0, .5 }, // 5: -x  0
        { -.5, -.5, .5 }, // 6: -x -y
        {  .0, -.5, .5 }, // 7:  0 -y
        {  .5, -.5, .5 }, // 8: +x -y
      }
    };

    static std::array<glm::vec3 const, 3> const o = {
      {
        { .05, .00, .00 },
        { .00, .05, .00 },
        { .00, .00, .05 },
      }
    };
    
    static std::array<vertex const, 40> const vertices = {
      {
        vertex(p[0], attr0), vertex(p[1], attr2),
        vertex(p[0], attr0), vertex(p[2], attr3),
        vertex(p[0], attr0), vertex(p[3], attr2),
        vertex(p[0], attr0), vertex(p[4], attr3),
        vertex(p[0], attr0), vertex(p[5], attr2),
        vertex(p[0], attr0), vertex(p[6], attr3),
        vertex(p[0], attr0), vertex(p[7], attr2),
        vertex(p[0], attr0), vertex(p[8], attr3),

        vertex(p[2]+o[0], attr0), vertex(p[6]+o[0], attr1),
        vertex(p[6]-o[0], attr0), vertex(p[2]-o[0], attr1),
        vertex(p[4]+o[0], attr0), vertex(p[8]+o[0], attr1),
        vertex(p[8]-o[0], attr0), vertex(p[4]-o[0], attr1),

        vertex(p[6]+o[0], attr0), vertex(p[4]+o[0], attr1),
        vertex(p[4]-o[0], attr0), vertex(p[6]-o[0], attr1),
        vertex(p[8]+o[0], attr0), vertex(p[2]+o[0], attr1),
        vertex(p[2]-o[0], attr0), vertex(p[8]-o[0], attr1),

        vertex(p[4]+o[1], attr0), vertex(p[2]+o[1], attr1),
        vertex(p[2]-o[1], attr0), vertex(p[4]-o[1], attr1),
        vertex(p[6]+o[1], attr0), vertex(p[8]+o[1], attr1),
        vertex(p[8]-o[1], attr0), vertex(p[6]-o[1], attr1),
      }
    };

    using line_list  = primitive::line_list;
    using vertex_list = line_list::vertex_list_type;
    
    pipeline_->process(line_list(vertex_list(vertices.begin(), vertices.end())));
  }
#endif
  
#if 1
  {
    static std::array<glm::vec3 const, 9> const p = {
      {
        {  .0,  .0, .0625 }, // 0:  0  0
        {  .3,  .0, .25 },   // 1: +x  0
        {  .3,  .3, .95 },   // 2: +x +y
        {  .0,  .3, .25 },   // 3:  0 +y
        { -.3,  .3, .95 },   // 4: -x +y
        { -.3,  .0, .25 },   // 5: -x  0
        { -.3, -.3, .95 },   // 6: -x -y
        {  .0, -.3, .25 },   // 7:  0 -y
        {  .3, -.3, .95 },   // 8: +x -y
      }
    };
    
    static std::array<glm::vec3 const, 4> const o = {
      {
        {  .05,  .05, .00 },
        { -.05,  .05, .00 },
        { -.05, -.05, .00 },
        {  .05, -.05, .00 },
      }
    };
    
    static std::array<vertex const, 33> const vertices = {
      {
        // ccw
        vertex(p[0]+o[0], attr0), vertex(p[1]+o[0], attr2), vertex(p[3]+o[0], attr3),
        vertex(p[0]+o[1], attr0), vertex(p[3]+o[1], attr3), vertex(p[5]+o[1], attr2),
        vertex(p[0]+o[2], attr0), vertex(p[5]+o[2], attr2), vertex(p[7]+o[2], attr3),
        vertex(p[0]+o[3], attr0), vertex(p[7]+o[3], attr3), vertex(p[1]+o[3], attr2),
        
        vertex(glm::vec3( 0.65,  0.00, .001), attr1),
        vertex(glm::vec3( 1.15, -1.15, .999), attr2),
        vertex(glm::vec3( 1.15,  1.15, .999), attr3),

        vertex(glm::vec3(-0.65,  0.00, .001), attr1),
        vertex(glm::vec3(-1.15,  1.15, .999), attr3),
        vertex(glm::vec3(-1.15, -1.15, .999), attr2),
        
        // cw
        vertex(p[0]+o[0], attr0), vertex(p[3]+o[0], attr3), vertex(p[1]+o[0], attr2),
        vertex(p[0]+o[1], attr0), vertex(p[5]+o[1], attr2), vertex(p[3]+o[1], attr3),
        vertex(p[0]+o[2], attr0), vertex(p[7]+o[2], attr3), vertex(p[5]+o[2], attr2),
        vertex(p[0]+o[3], attr0), vertex(p[1]+o[3], attr2), vertex(p[7]+o[3], attr3),

        vertex(glm::vec3( 0.65,  0.00, .001), attr1),
        vertex(glm::vec3( 1.15,  1.15, .999), attr2),
        vertex(glm::vec3( 1.15, -1.15, .999), attr3),

        //vertex(glm::vec3(-0.65,  0.00, .001), attr1),
        //vertex(glm::vec3(-1.15, -1.15, .999), attr3),
        //vertex(glm::vec3(-1.15,  1.15, .999), attr2),
      }
    };

    using triangle_list = primitive::triangle_list;
    using vertex_list   = triangle_list::vertex_list_type;
    
    pipeline_->process(triangle_list(vertex_list(vertices.begin(), vertices.end())));
  }
#endif
  
  win_color_->queue_draw();
  win_depth_->queue_draw();
  /*       */ queue_draw();
}
