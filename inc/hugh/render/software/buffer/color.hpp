// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/buffer/color.hpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_BUFFER_COLOR_HPP)

#define HUGH_RENDER_SOFTWARE_BUFFER_COLOR_HPP

// includes, system

#include <glm/glm.hpp> // glm::*
#include <vector>      // std::vector<>

// includes, project

#include <hugh/render/software/buffer/base.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace buffer {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT color : public base {

        public:
          
          explicit color(viewport_type const& = viewport_type());
          virtual ~color();

          virtual void clear ();
          virtual bool update(fragment const&);

        private:

          using buffer_type = std::vector<glm::vec4>;
          
          buffer_type::value_type const clear_value_;
          buffer_type                   buffer_;
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace buffer {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_BUFFER_COLOR_HPP)
