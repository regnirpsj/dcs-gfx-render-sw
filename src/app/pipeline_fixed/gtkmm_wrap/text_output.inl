// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/text_output.inl                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_TEXT_OUTPUT_INL)

#define HUGH_APP_GTKMM_TEXT_OUTPUT_INL

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

    template <typename T>
    /* static */ unsigned const text_output<T>::default_width(58);
    
    // functions, inlined (inline)

    template <typename T>
    inline /* explicit */
    text_output<T>::text_output(std::string const&      a,
                                get_value_function_type b,
                                std::string const&      c,
                                unsigned                d)
      : Gtk::HBox         (),
        boost::noncopyable(),
        label_text_       ("", Gtk::ALIGN_END),
        label_value_      ("", Gtk::ALIGN_START),
        get_value_        (b)
    {
      TRACE("hugh::gtkmm::text_output<" + support::demangle(typeid(T)) + ">::text_output");
      
      set_border_width(1);
      set_spacing     (1);
    
      if (!a.empty()) {
        label_text_.set_text       (a);
        label_text_.set_width_chars(label_text_.get_text().length());
        label_text_.set_justify    (Gtk::JUSTIFY_RIGHT);
    
        if (!c.empty()) {
          label_text_.set_tooltip_markup(c);
        }
      
        pack_start(label_text_, Gtk::PACK_SHRINK);
      }

      update();
        
      {
        label_value_.set_selectable (true);
        label_value_.set_width_chars(d - label_value_.get_text().length());
        label_value_.set_justify    (Gtk::JUSTIFY_RIGHT);

        pack_start(label_value_, Gtk::PACK_SHRINK);
      }
    }
    
    template <typename T>
    inline /* virtual */ bool
    text_output<T>::on_draw(::Cairo::RefPtr<::Cairo::Context> const& cr)
    {
      TRACE("hugh::gtkmm::text_output<" + support::demangle(typeid(T)) + ">::on_draw");

      update();
        
      return Gtk::HBox::on_draw(cr);
    }
      
    template <typename T>
    inline void
    text_output<T>::update()
    {
      TRACE("hugh::gtkmm::text_output<" + support::demangle(typeid(T)) + ">::update");
      
      try {
        label_value_.set_text(boost::lexical_cast<std::string>(get_value_()));
      }
      
      catch (boost::bad_lexical_cast const&) {
        label_value_.set_text("<undefined>");
      }
    }

  } // namespace gtkmm {
  
} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_APP_GTKMM_TEXT_OUTPUT_INL)
