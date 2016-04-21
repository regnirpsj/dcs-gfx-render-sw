// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/check_button_input.hpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_CHECK_BUTTON_INPUT_HPP)

#define HUGH_APP_GTKMM_CHECK_BUTTON_INPUT_HPP

// includes, system

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <functional>            // std::function<>
#include <gtkmm/box.h>           // Gtk::HBox
#include <gtkmm/checkbutton.h>   // Gtk::CheckButton
#include <gtkmm/label.h>         // Gtk::Label
#include <string>                // std::string

// includes, project

// #include <>

namespace hugh {

  namespace gtkmm {
    
    // types, exported (class, enum, struct, union, typedef)
    
    template <typename Type>
    class check_button_input : public Gtk::HBox,
                               private boost::noncopyable {

    public:

      typedef std::function<Type ()>            get_value_function_type;
      typedef std::function<Type (Type const&)> set_value_function_type;

      explicit check_button_input(std::string const&,
                                  get_value_function_type,
                                  set_value_function_type,
                                  std::string const&,
                                  bool = true,
                                  bool = false);
      virtual ~check_button_input();

      void refresh();
    
    private:
    
      void on_clicked();
    
      Gtk::Label              label_;
      Gtk::CheckButton        check_btn_;
      get_value_function_type get_value_;
      set_value_function_type set_value_;
      bool const              editable_;
      bool const              immediate_;
    
    };
    
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

  } // namespace gtkmm {
  
} // namespace hugh {

#include <gtkmm_wrap/check_button_input.inl>

#endif // #if !defined(HUGH_APP_GTKMM_CHECK_BUTTON_INPUT_HPP)
