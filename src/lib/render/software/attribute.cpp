// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/attribute.cpp                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/attribute.hpp"

// includes, system

#include <glm/gtx/io.hpp> // glm::operator<<
#include <ostream>        // std::ostream

// includes, project

#include <hugh/support/io_utils.hpp>

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

      namespace attribute {
        
        // variables, exported
  
        // functions, exported

        std::ostream&
        operator<<(std::ostream& os, type const& a)
        {
          TRACE_NEVER("hugh::render::software::attribute::operator<<(type)");

          std::ostream::sentry const cerberus(os);

          if (cerberus) {
            os << '[';

            switch (a) {
            case type::position:  os << "POSITION";                        break;
            case type::normal:    os << "NORMAL";                          break;
            case type::color:     os << "COLOR";                           break;
            case type::texcoord:  os << "TEXCOORD";                        break;
            case type::bitangent: os << "BITANGENT";                       break;
            default:              os << "UNKNOWN (" << unsigned(a) << ')'; break;
            }
            
            os << ']';
          }

          return os;
        }
        
      } // namespace attribute {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
