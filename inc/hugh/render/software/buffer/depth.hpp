// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/buffer/depth.hpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_BUFFER_DEPTH_HPP)

#define HUGH_RENDER_SOFTWARE_BUFFER_DEPTH_HPP

// includes, system

#include <glm/gtc/vec1.hpp> // glm::vec1
#include <vector>           // std::vector<>

// includes, project

#include <hugh/render/software/buffer/base.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace buffer {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT depth : public base {

        public:

          field::value::single<glm::vec1> clear_value; //< dflt: [1]
          
          explicit depth(viewport_type const& = viewport_type());
          virtual ~depth();

          inline glm::vec1 const& operator[](unsigned a) const
          {
            return buffer_[a];
          }

          virtual void clear ();
          virtual bool update(fragment const&);
          
          bool zcull(fragment const&) const;
          bool ztest(fragment const&);

        private:

          using buffer_type = std::vector<glm::vec1>;
          
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

//#include <hugh/render/software/buffer/depth.inl>

#endif // #if !defined(HUGH_RENDER_SOFTWARE_BUFFER_DEPTH_HPP)
