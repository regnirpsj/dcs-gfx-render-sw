// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/attribute.hpp                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_ATTRIBUTE_HPP)

#define HUGH_RENDER_SOFTWARE_ATTRIBUTE_HPP

// includes, system

#include <glm/glm.hpp>   // glm::*
#include <iosfwd>        // std::ostream (fwd decl)
#include <unordered_map> // std::unordered_map<>

// includes, project

#include <hugh/render/software/export.h>

namespace hugh {

  namespace render {

    namespace software {

      namespace attribute {
        
        // types, exported (class, enum, struct, union, typedef)

        enum class type {
          position,
          normal,
          color,
          texcoord,
          bitangent,
        };
        
        using list = std::unordered_map<type, glm::vec4>;
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

        HUGH_RENDER_SOFTWARE_EXPORT std::ostream& operator<<(std::ostream&, type const&);
        
      } // namespace attribute {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

namespace std {
  
  template <>
  struct hash<hugh::render::software::attribute::type> {

    using attribute_type = hugh::render::software::attribute::type;
    
    inline size_t operator()(attribute_type const& a) const
    {
      return hash<underlying_type<attribute_type>::type>()(unsigned(a));
    }
    
  };

} // namespace std {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_ATTRIBUTE_HPP)
