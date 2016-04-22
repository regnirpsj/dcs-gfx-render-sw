// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/check_button_input.inl                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_CHECK_BUTTON_INPUT_INL)

#define HUGH_APP_GTKMM_CHECK_BUTTON_INPUT_INL

// includes, system

//#include <>

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
#if defined(HUGH_USE_TRACE) || defined(HUGH_ALL_TRACE)
#  include <typeinfo>
#  include <hugh/support/type_info.hpp>
#endif

namespace hugh {

  namespace gtkmm {
    
    // functions, inlined (inline)

    template <typename T>
    inline /* explicit */
    check_button_input<T>::check_button_input(std::string const&      a,
                                              get_value_function_type b,
                                              set_value_function_type c,
                                              std::string const&      d,
                                              bool                    e,
                                              bool                    f)
      : Gtk::HBox         (),
        boost::noncopyable(),
        label_            (a, Gtk::ALIGN_END),
        check_btn_        (),
        get_value_        (b),
        set_value_        (c),
        editable_         (e),
        immediate_        (f)
    {
      TRACE("hugh::gtkmm::check_button_input<" + support::demangle(typeid(T)) +
            ">::check_button_input");
      
      set_border_width(1);
      
      if (!a.empty()) {
        label_.set_justify    (Gtk::JUSTIFY_RIGHT);
        label_.set_width_chars(label_.get_text().length());

        if (!d.empty()) {
          label_.set_tooltip_markup(d);
        }
      
        pack_start(label_, Gtk::PACK_SHRINK);
      }
      
      {
        check_btn_.set_active   (get_value_());
        check_btn_.set_sensitive(editable_);

        if (!d.empty()) {
          check_btn_.set_tooltip_markup(d);
        }
      }

      pack_start(check_btn_, Gtk::PACK_SHRINK);
      
      if (editable_ && immediate_) {
        check_btn_.signal_clicked().
          connect(sigc::mem_fun(this, &check_button_input<T>::on_clicked));
      }
    }
    
    template <typename T>
    inline /* virtual */
    check_button_input<T>::~check_button_input()
    {
      TRACE("hugh::gtkmm::check_button_input<" + support::demangle(typeid(T)) +
            ">::~check_button_input");
      
      if (editable_ && !immediate_) {
        on_clicked();
      }
    }

    template <typename T>
    inline void
    check_button_input<T>::refresh()
    {
      TRACE("hugh::gtkmm::check_button_input<" + support::demangle(typeid(T)) + ">::refresh");
      
      if (editable_) {
        T const tmp(get_value_());
        
        if (check_btn_.get_active() != tmp) {
          check_btn_.set_active(tmp);
        }
      }
    }
    
    template <typename T>
    inline void
    check_button_input<T>::on_clicked()
    {
      TRACE("hugh::gtkmm::check_button_input<" + support::demangle(typeid(T)) + ">::on_clicked");

      bool const tmp(check_btn_.get_active());
      
      if (get_value_() != tmp) {
        set_value_(tmp);
      }
    }
    
  } // namespace gtkmm {
  
} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_APP_GTKMM_CHECK_BUTTON_INPUT_INL)
