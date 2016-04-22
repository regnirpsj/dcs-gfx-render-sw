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

#include <vector> // std::vector<>

// includes, project

#include <hugh/render/software/buffer/base.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace buffer {
        
        // types, exported (class, enum, struct, union, typedef)
        
        class HUGH_RENDER_SOFTWARE_EXPORT color : public base {

        public:
          
          field::value::single<glm::vec4> clear_value; //< dflt: [0,0,0,0]
          
          explicit color(viewport_type const& = viewport_type());
          virtual ~color();
          
          inline glm::vec4 const& operator[](unsigned a) const
          {
            return buffer_[a];
          }

          virtual void clear ();
          virtual bool update(fragment const&);

        private:

          using buffer_type = std::vector<glm::vec4>;
          
          buffer_type buffer_;

          virtual void do_changed(field::base&);
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace buffer {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

//#include <hugh/render/software/buffer/color.inl>

#endif // #if !defined(HUGH_RENDER_SOFTWARE_BUFFER_COLOR_HPP)
