// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/text_output.hpp                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_TEXT_OUTPUT_HPP)

#define HUGH_APP_GTKMM_TEXT_OUTPUT_HPP

// includes, system

#include <boost/lexical_cast.hpp> // boost::lexical_cast<>
#include <boost/noncopyable.hpp>  // boost::noncopyable
#include <functional>             // std::function<>
#include <gtkmm/box.h>            // Gtk::HBox
#include <gtkmm/label.h>          // Gtk::Label
#include <string>                 // std::string

// includes, project

// #include <>

namespace hugh {

  namespace gtkmm {
    
    // types, exported (class, enum, struct, union, typedef)

    template <typename T>
    class text_output : public Gtk::HBox, private boost::noncopyable {

    public:

      static unsigned const default_width; // == 58

      using get_value_function_type = std::function<T ()>;
      
      explicit text_output(std::string const&,
                           get_value_function_type,
                           std::string const&,
                           unsigned = default_width);
      
    private:

      Gtk::Label              label_text_;
      Gtk::Label              label_value_;
      get_value_function_type get_value_;
      
      virtual bool on_draw(::Cairo::RefPtr<::Cairo::Context> const&);

      void update();
      
    };
    
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

  } // namespace gtkmm {
  
} // namespace hugh {

#include <gtkmm_wrap/text_output.inl>

#endif // #if !defined(HUGH_APP_GTKMM_TEXT_OUTPUT_HPP)
