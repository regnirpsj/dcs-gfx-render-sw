// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/radio_button_input.hpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_RADIO_BUTTON_INPUT_HPP)

#define HUGH_APP_GTKMM_RADIO_BUTTON_INPUT_HPP

// includes, system

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <functional>            // std::function<>
#include <gtkmm/alignment.h>     // Gtk::Alignment
#include <gtkmm/box.h>           // Gtk::HBox
#include <gtkmm/label.h>         // Gtk::Label
#include <gtkmm/radiobutton.h>   // Gtk::RadioButton
#include <string>                // std::string
#include <vector>                // std::vector<>

// includes, project

// #include <>

namespace hugh {

  namespace gtkmm {
    
    // types, exported (class, enum, struct, union, typedef)
    
    template <typename T>
    class radio_button_input : private boost::noncopyable {

    public:
    
      virtual ~radio_button_input();
    
    protected:

      using get_value_function_type = std::function<T ()>;
      using set_value_function_type = std::function<T (T const&)>;

      Gtk::Label                     label_;
      std::vector<Gtk::RadioButton*> radio_buttons_;
      unsigned                       active_button_;
      get_value_function_type        get_value_;
      set_value_function_type        set_value_;
      bool                           editable_;
      bool                           immediate_;
      
      explicit radio_button_input(std::string const&,
                                  get_value_function_type,
                                  set_value_function_type,
                                  std::string const&,
                                  std::vector<std::string> const&,
                                  bool,
                                  bool);
    
      void on_button_activate(unsigned);
    
    };

    template <typename T>
    class hradio_button_input : public Gtk::HBox,
                                public radio_button_input<T> {

    public:

      using inherited_rbi           = radio_button_input<T>;
      using get_value_function_type = typename inherited_rbi::get_value_function_type;
      using set_value_function_type = typename inherited_rbi::set_value_function_type;
    
      explicit hradio_button_input(std::string const&,
                                   get_value_function_type,
                                   set_value_function_type,
                                   std::string const&,
                                   std::vector<std::string> const&,
                                   bool = true,
                                   bool = false);
    
    };

    template <typename T>
    class vradio_button_input : public Gtk::VBox,
                                public radio_button_input<T> {

    public:

      using inherited_rbi           = radio_button_input<T>;
      using get_value_function_type = typename inherited_rbi::get_value_function_type;
      using set_value_function_type = typename inherited_rbi::set_value_function_type;
    
      explicit vradio_button_input(std::string const&,
                                   get_value_function_type,
                                   set_value_function_type,
                                   std::string const&,
                                   std::vector<std::string> const&,
                                   bool = true,
                                   bool = false);
    
    };
    
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

  } // namespace gtkmm {
  
} // namespace hugh {

#include <gtkmm_wrap/radio_button_input.inl>

#endif // #if !defined(HUGH_APP_GTKMM_RADIO_BUTTON_INPUT_HPP)
