// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/pipeline/base.cpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/pipeline/base.hpp"

// includes, system

#define BOOST_THREAD_PROVIDES_EXECUTORS
#define BOOST_THREAD_PROVIDES_FUTURE
#include <boost/thread/future.hpp> // boost::future<>
#include <glm/gtx/io.hpp>          // glm::operator<<
#include <stdexcept>               // std::logic_error

// includes, project

//#include <>

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

      namespace pipeline {
        
        // variables, exported
  
        // functions, exported

        base::statistics::statistics()
          : fragments({ 0, 0, }),
            vertices ({ 0, })
        {
          TRACE("hugh::render::software::pipeline::base::statistics::statistics");
        }
        
        base::statistics&
        base::statistics::operator+=(statistics const& a)
        {
          TRACE_NEVER("hugh::render::software::pipeline::base::statistics::operator+=");

          fragments.created  += a.fragments.created;
          fragments.updated  += a.fragments.updated;
          vertices.processed += a.vertices.processed;
          
          return *this;
        }
        
        /* virtual */
        base::~base()
        {
          TRACE("hugh::render::software::pipeline::base::~base");
        }

        /* virtual */ void
        base::process(primitive::base const&)
        {
          TRACE_NEVER("hugh::render::software::pipeline::base::process");

          throw std::logic_error("pure virtual function "
                                 "'hugh::render::software::pipeline::base::process' called");
        }
          
        glm::vec4
        base::object_to_world(glm::vec4 const& a) const
        {
          TRACE_NEVER("hugh::render::software::pipeline::base::object_to_world");

          return (*xform_model * a);
        }
        
        glm::vec4
        base::world_to_eye(glm::vec4 const& a) const
        {
          TRACE_NEVER("hugh::render::software::pipeline::base::world_to_eye");

          return (*xform_view * a);
        }
        
        glm::vec4
        base::eye_to_clip(glm::vec4 const& a) const
        {
          TRACE_NEVER("hugh::render::software::pipeline::base::eye_to_clip");

          return (*xform_projection * a);
        }
        
        glm::vec3
        base::clip_to_ndc(glm::vec4 const& a) const
        {
          TRACE_NEVER("hugh::render::software::pipeline::base::clip_to_ndc");

          return glm::vec3(a.x / a.w, a.y / a.w, a.z / a.w);
        }
        
        /* explicit */
        base::base(unsigned a)
          : field::container         (),
            support::refcounted<base>(),
            xform_model              (*this, "xform_model"),
            xform_view               (*this, "xform_view"),
            xform_projection         (*this, "xform_projection"),
            lights                   (*this, "lights"),
            material                 (*this, "material"),
            rasterizer               (*this, "rasterizer",  nullptr),
            colorbuffer              (*this, "colorbuffer", nullptr),
            depthbuffer              (*this, "depthbuffer", nullptr),
            stats                    (*this, "stats"),
            thread_pool_             (a)
        {
          TRACE("hugh::render::software::pipeline::base::base");
        }

        template <>
        base::fragment_list_type
        base::raster<primitive::topology::point_list>(index_list_type const&  ilist,
                                                      vertex_list_type const& vlist,
                                                      bool async)
        {
          TRACE("hugh::render::software::pipeline::base::raster"
                "<primitive::topology::point_list>");

          fragment_list_type result;
          
          if (async) { // task parallel
            std::vector<boost::future<fragment_list_type>> futures;

            futures.reserve(ilist.empty() ? vlist.size() : ilist.size());

            if (ilist.empty()) {
              for (auto const& v : vlist) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_vertex,
                                               rasterizer.get(),
                                               v));
              }
            } else {
              for (auto const& i : ilist) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_vertex,
                                               rasterizer.get(),
                                               vlist[i]));
              }
            }
          
            for (auto& f : futures) {            
              fragment_list_type const fl(f.get());

              result.insert(result.end(), fl.begin(), fl.end());
            }
          } else { // task sequential
            if (ilist.empty()) {
              for (auto const& v : vlist) {
                fragment_list_type const fl((*rasterizer)->process(v));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            } else {
              for (auto const& i : ilist) {
                fragment_list_type const fl((*rasterizer)->process(vlist[i]));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            }
          }
          
          return result;
        }
        
        template <>
        base::fragment_list_type
        base::raster<primitive::topology::line_list>(index_list_type const&  ilist,
                                                     vertex_list_type const& vlist,
                                                     bool async)
        {
          TRACE("hugh::render::software::pipeline::base::raster"
                "<primitive::topology::line_list>");

          fragment_list_type result;
          
          if (async) { // task parallel
            std::vector<boost::future<fragment_list_type>> futures;

            futures.reserve((ilist.empty() ? vlist.size() : ilist.size()) / 2);
          
            if (ilist.empty()) {
              for (unsigned i(0); i < vlist.size(); i += 2) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_line,
                                               rasterizer.get(),
                                               line(vlist[i+0],
                                                    vlist[i+1])));
              }
            } else {
              for (unsigned i(0); i < ilist.size(); i += 2) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_line,
                                               rasterizer.get(),
                                               line(vlist[ilist[i+0]],
                                                    vlist[ilist[i+1]])));
              }
            }
          
            for (auto& f : futures) {            
              fragment_list_type const& fl(f.get());

              result.insert(result.end(), fl.begin(), fl.end());
            }
          } else { // task sequential
            if (ilist.empty()) {
              for (unsigned i(0); i < vlist.size(); i += 2) {
                fragment_list_type const fl((*rasterizer)->process(line(vlist[i+0],
                                                                        vlist[i+1])));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            } else {
              for (unsigned i(0); i < ilist.size(); i += 2) {
                fragment_list_type const fl((*rasterizer)->process(line(vlist[ilist[i+0]],
                                                                        vlist[ilist[i+1]])));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            }
          }
          
          return result;
        }

        template <>
        base::fragment_list_type
        base::raster<primitive::topology::line_strip>(index_list_type const&  ilist,
                                                      vertex_list_type const& vlist,
                                                      bool async)
        {
          TRACE("hugh::render::software::pipeline::base::raster"
                "<primitive::topology::line_strip>");

          fragment_list_type result;

          if (async) { // task parallel
            std::vector<boost::future<fragment_list_type>> futures;

            futures.reserve((ilist.empty() ? vlist.size() : ilist.size()) - 1);
          
            if (ilist.empty()) {
              for (unsigned i(0); i < vlist.size()-1; ++i) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_line,
                                               rasterizer.get(),
                                               line(vlist[i+0],
                                                    vlist[i+1])));
              }
            } else {
              for (unsigned i(0); i < ilist.size()-1; ++i) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_line,
                                               rasterizer.get(),
                                               line(vlist[ilist[i+0]],
                                                    vlist[ilist[i+1]])));
              }
            }
          
            for (auto& f : futures) {            
              fragment_list_type const& fl(f.get());

              result.insert(result.end(), fl.begin(), fl.end());
            }
          } else { // task sequential
            if (ilist.empty()) {
              for (unsigned i(0); i < vlist.size()-1; ++i) {
                fragment_list_type const fl((*rasterizer)->process(line(vlist[i+0],
                                                                        vlist[i+1])));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            } else {
              for (unsigned i(0); i < ilist.size()-1; ++i) {
                fragment_list_type const fl((*rasterizer)->process(line(vlist[ilist[i+0]],
                                                                        vlist[ilist[i+1]])));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            }
          }
          
          return result;
        }

        template <>
        base::fragment_list_type
        base::raster<primitive::topology::triangle_list>(index_list_type const&  ilist,
                                                         vertex_list_type const& vlist,
                                                         bool async)
        {
          TRACE("hugh::render::software::pipeline::base::raster"
                "<primitive::topology::triangle_list>");

          fragment_list_type result;

          if (async) { // task parallel
            std::vector<boost::future<fragment_list_type>> futures;

            futures.reserve((ilist.empty() ? vlist.size() : ilist.size()) / 3);
          
            if (ilist.empty()) {
              for (unsigned i(0); i < vlist.size(); i += 3) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_triangle,
                                               rasterizer.get(),
                                               triangle(vlist[i+0],
                                                        vlist[i+1],
                                                        vlist[i+2])));
              }
            } else {
              for (unsigned i(0); i < ilist.size(); i += 3) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_triangle,
                                               rasterizer.get(),
                                               triangle(vlist[ilist[i+0]],
                                                        vlist[ilist[i+1]],
                                                        vlist[ilist[i+2]])));
              }
            }
          
            for (auto& f : futures) {            
              fragment_list_type const& fl(f.get());

              result.insert(result.end(), fl.begin(), fl.end());
            }
          } else { // task sequential
            if (ilist.empty()) {
              for (unsigned i(0); i < vlist.size(); i += 3) {
                fragment_list_type const fl((*rasterizer)->process(triangle(vlist[i+0],
                                                                            vlist[i+1],
                                                                            vlist[i+2])));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            } else {
              for (unsigned i(0); i < ilist.size(); i += 3) {
                fragment_list_type const fl((*rasterizer)->process(triangle(vlist[ilist[i+0]],
                                                                            vlist[ilist[i+1]],
                                                                            vlist[ilist[i+2]])));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            }
          }
          
          return result;
        }

        template <>
        base::fragment_list_type
        base::raster<primitive::topology::triangle_strip>(index_list_type const&  ilist,
                                                          vertex_list_type const& vlist,
                                                          bool async)
        {
          TRACE("hugh::render::software::pipeline::base::raster"
                "<primitive::topology::triangle_strip>");

          fragment_list_type result;

          if (async) { // task parallel
            std::vector<boost::future<fragment_list_type>> futures;

            futures.reserve((ilist.empty() ? vlist.size() : ilist.size()) - 2);
            
            if (ilist.empty()) {
              for (unsigned i(0); i < vlist.size()-2; ++i) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_triangle,
                                               rasterizer.get(),
                                               triangle(vlist[i+0],
                                                        vlist[i+1],
                                                        vlist[i+2])));
              }
            } else {
              for (unsigned i(0); i < ilist.size()-2; ++i) {
                futures.push_back(boost::async(thread_pool_,
                                               &rasterizer::base::process_triangle,
                                               rasterizer.get(),
                                               triangle(vlist[ilist[i+0]],
                                                        vlist[ilist[i+1]],
                                                        vlist[ilist[i+2]])));
              }
            }
          
            for (auto& f : futures) {            
              fragment_list_type const fl(f.get());

              result.insert(result.end(), fl.begin(), fl.end());
            }
          } else { // task sequential
            if (ilist.empty()) {
              for (unsigned i(0); i < vlist.size()-2; ++i) {
                fragment_list_type const fl((*rasterizer)->process(triangle(vlist[i+0],
                                                                            vlist[i+1],
                                                                            vlist[i+2])));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            } else {
              for (unsigned i(0); i < ilist.size()-2; ++i) {
                fragment_list_type const fl((*rasterizer)->process(triangle(vlist[ilist[i+0]],
                                                                            vlist[ilist[i+1]],
                                                                            vlist[ilist[i+2]])));

                result.insert(result.end(), fl.begin(), fl.end());
              }
            }
          }
          
          return result;
        }
        
        std::ostream&
        operator<<(std::ostream& os, base::statistics const& a)
        {
          TRACE_NEVER("hugh::render::software::pipeline::operator<<(base::statistics)");

          std::ostream::sentry const cerberus(os);

          if (cerberus) {
            os << '['
               << "v:"
               << a.vertices.processed
               << " -> f:"
               << a.fragments.created
               << " -> p:"
               << a.fragments.updated
               << ']';
          }

          return os;
        }

      } // namespace pipeline {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
