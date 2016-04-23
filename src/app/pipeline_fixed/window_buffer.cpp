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
#undef HUGH_USE_TRACE
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

  using ImageSurface = ::Cairo::ImageSurface;
  
  ::Cairo::RefPtr<ImageSurface> dst(ImageSurface::create(::Cairo::FORMAT_RGB24, size.x, size.y));

  unsigned const dst_row_len(dst->get_stride());
  guint8*        dst_data   (dst->get_data());
  unsigned       buf_idx(0);
  
  for (unsigned y(0); y < size.y; ++y) {
    for (unsigned x(0); x < dst_row_len; x += 4) {
      switch (type_) {
      case type::color:
        {
          glm::vec4 const& src(static_cast<cbuffer_type const&>(*buffer_)[buf_idx]);
      
          *(dst_data + ((y * dst_row_len) + x + 0)) = 255 * src.b; // b
          *(dst_data + ((y * dst_row_len) + x + 1)) = 255 * src.g; // g
          *(dst_data + ((y * dst_row_len) + x + 2)) = 255 * src.r; // r
          *(dst_data + ((y * dst_row_len) + x + 3)) = 255 * src.a; // a
        }
        break;

      case type::depth:
        {
          glm::vec1 const& src(static_cast<dbuffer_type const&>(*buffer_)[buf_idx]);
      
          *(dst_data + ((y * dst_row_len) + x + 0)) = 255 * src.x;  // b
          *(dst_data + ((y * dst_row_len) + x + 1)) = 255 * src.x;  // g
          *(dst_data + ((y * dst_row_len) + x + 2)) = 255 * src.x;  // r
          *(dst_data + ((y * dst_row_len) + x + 3)) = 255;          // a
        }
        break;

      default:
        {
          throw std::runtime_error("window_buffer::on_draw: unrecognized buffe type (" +
                                   std::to_string(unsigned(type_)) + ")");
        }
        break;
      }

      ++buf_idx;
    }
  }

  cr->set_identity_matrix();
  {
    glm::vec2 const alloc(get_allocation().get_width(), get_allocation().get_height());
    double const    xx( alloc.x / size.x);
    double const    yx( 0.0);
    double const    xy( 0.0);
    double const    yy(-alloc.y / size.y);
    double const    x0( 0.0);
    double const    y0( alloc.y);
    
    cr->set_matrix(::Cairo::Matrix(xx, yx, xy, yy, x0, y0));
  }
  cr->set_source(dst, 0, 0);
  cr->paint     ();
  
  return true;
}
