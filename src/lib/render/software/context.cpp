// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/context.cpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/context.hpp"

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/pipeline/fixed.hpp>
#include <hugh/render/software/rasterizer/simple.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {

  namespace render {

    namespace software {

      // variables, exported
  
      // functions, exported

      /* explicit */
      context::context(viewport_type const& a)
        : field::container(),
          viewport        (*this, "viewport",    a),
          colorbuffer     (*this, "colorbuffer", nullptr),
          depthbuffer     (*this, "depthbuffer", nullptr),
          rasterizer      (*this, "rasterizer",  nullptr),
          pipeline        (*this, "pipeline",    nullptr)
      {
        TRACE("hugh::render::software::context::context");

        viewport.touch();
      }
      
      /* virtual */
      context::~context()
      {
        TRACE("hugh::render::software::context::~context");
      }
      
      /* virtual */ void
      context::clear()
      {
        TRACE("hugh::render::software::context::clear");

        if (*depthbuffer) { (*depthbuffer)->clear(); }
        if (*colorbuffer) { (*colorbuffer)->clear(); }
      }

      /* virtual */ void
      context::submit()
      {
        TRACE("hugh::render::software::context::submit");
      }

      /* virtual */ void
      context::flush()
      {
        TRACE("hugh::render::software::context::flush");
      }

      /* virtual */ void
      context::do_evaluate()
      {
        TRACE("hugh::render::software::context::do_evaluate");

#if 0
        // would need to set other field-container fields and plays against container eval (somehow)
        if ((viewport.last_change() > last_evaluate_) &&
            (viewport.last_change() < last_change_)) {
          std::cout << support::trace::prefix() << "hugh::render::software::context::do_evaluate: "
                    << "vp needs eval"
                    << '\n';
        }
#endif
        
        field::container::do_evaluate();
      }
      
      /* virtual */ void
      context::do_changed(field::base& f)
      {
        TRACE("hugh::render::software::context::do_changed");

        if (&f == &viewport) {
          viewport_type const vp(viewport->x,
                                 viewport->y,
                                 std::min(float(1), viewport->width),
                                 std::min(float(1), viewport->height),
                                 viewport->near,
                                 viewport->far);
          
          colorbuffer.set(new buffer::color     (vp));
          depthbuffer.set(new buffer::depth     (vp));
          rasterizer .set(new rasterizer::simple(vp));
          pipeline   .set(new pipeline::fixed);

          (*pipeline)->colorbuffer.set(*colorbuffer);
          (*pipeline)->depthbuffer.set(*depthbuffer);
          (*pipeline)->rasterizer .set(*rasterizer);
        }

        else if (&f == &colorbuffer) { /* ??? */ }
        else if (&f == &depthbuffer) { /* ??? */ }
        else if (&f == &rasterizer)  { /* ??? */ }
        else if (&f == &pipeline)    { /* ??? */ }

        else {
          field::container::do_changed(f);
        }
      }
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
