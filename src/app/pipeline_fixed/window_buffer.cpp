// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  pipeline_fixed/window_buffer.cpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "window_buffer.hpp"

// includes, system

#include <gdkmm/general.h> // Gdk::*::set_source_pixbuf()
#include <stdexcept>       // std::runtime_error

// includes, project

#include <hugh/render/software/buffer/color.hpp>
#include <hugh/render/software/buffer/depth.hpp>

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
window_buffer::window_buffer(std::string const& a, cbuffer_type* b)
  : window_buffer(a, b, type::color)
{
  TRACE("window_buffer::window_buffer(buffer::color)");
}

/* explicit */
window_buffer::window_buffer(std::string const& a, dbuffer_type* b)
  : window_buffer(a, b, type::depth)
{
  TRACE("window_buffer::window_buffer(buffer::depth)");
}

/* virtual */
window_buffer::~window_buffer()
{
  TRACE("window_buffer::~window_buffer");
}

/* explicit */
window_buffer::window_buffer(std::string const& a, buffer_type* b, type c)
  : hugh::gtkmm::window(),
    buffer_            (b),
    type_              (c)
{
  TRACE("window_buffer::window_buffer(buffer::base)");

  if (!buffer_) {
    throw std::runtime_error("window_buffer::window_buffer: "
                             "buffer argument cannot be a null pointer");
  }

  {
    buffer_type::viewport_type const& vp(*buffer_->viewport);
    
    set_size_request(vp.width - vp.x, vp.height - vp.y);
  }

  show_all();
  
  set_title(a + ": " + ((type_ == type::color) ? "color" : "depth"));
}

/* virtual */ bool
window_buffer::on_draw(::Cairo::RefPtr<::Cairo::Context> const& cr)
{
  TRACE("window_buffer::on_draw");

  buffer_type::viewport_type const& vp  (*buffer_->viewport);
  glm::uvec2 const                  size(vp.width - vp.x, vp.height - vp.y);

  ::Cairo::RefPtr<::Cairo::ImageSurface> img(::Cairo::ImageSurface::create(::Cairo::FORMAT_RGB24,
                                                                           size.x, size.y));

  unsigned idx(0);
  
  for (unsigned y(0); y < unsigned(img->get_height()); ++y) {
    for (unsigned x(0); x < unsigned(img->get_stride()); x += 4) {
      switch (type_) {
      case type::color:
        {
          glm::vec4 const& c(static_cast<cbuffer_type const&>(*buffer_)[idx]);
      
          *(img->get_data() + ((y * img->get_stride()) + x + 0)) = 255 * c.b; // b
          *(img->get_data() + ((y * img->get_stride()) + x + 1)) = 255 * c.g; // g
          *(img->get_data() + ((y * img->get_stride()) + x + 2)) = 255 * c.r; // r
          *(img->get_data() + ((y * img->get_stride()) + x + 3)) = 255 * c.a; // a
        }
        break;

      case type::depth:
        {
          glm::vec1 const& d(static_cast<dbuffer_type const&>(*buffer_)[idx]);
      
          *(img->get_data() + ((y * img->get_stride()) + x + 0)) = 255 * d.x;  // b
          *(img->get_data() + ((y * img->get_stride()) + x + 1)) = 255 * d.x;  // g
          *(img->get_data() + ((y * img->get_stride()) + x + 2)) = 255 * d.x;  // r
          *(img->get_data() + ((y * img->get_stride()) + x + 3)) = 255;        // a
        }
        break;

      default:
        {
          throw std::runtime_error("window_buffer::on_draw: unrecognized buffe type (" +
                                   std::to_string(unsigned(type_)) + ")");
        }
        break;
      }

      ++idx;
    }
  }
  
  cr->scale     (get_allocation().get_width()  / double(size.x),
                 get_allocation().get_height() / double(size.y));
  cr->set_source(img, 0, 0);
  cr->paint     ();
  
  return false;
}
