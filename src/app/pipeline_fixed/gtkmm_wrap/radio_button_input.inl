// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/radio_button_input.inl                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_RADIO_BUTTON_INPUT_INL)

#define HUGH_APP_GTKMM_RADIO_BUTTON_INPUT_INL

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
    inline /* virtual */
    radio_button_input<T>::~radio_button_input()
    {
      TRACE("hugh:gtkmm::radio_button_input<" + support::demangle(typeid(T)) +
            ">::~radio_button_input");
      
      if (editable_ && !immediate_ && (get_value_() != static_cast<T>(active_button_))) {
        set_value_(static_cast<T>(active_button_));
      }
    }

    template <typename T>
    inline /* explicit */
    radio_button_input<T>::radio_button_input(std::string const&              a,
                                              get_value_function_type         b,
                                              set_value_function_type         c,
                                              std::string const&              d,
                                              std::vector<std::string> const& e,
                                              bool                            f,
                                              bool                            g)
      : boost::noncopyable(),
        label_            (a),
        radio_buttons_    (),
        active_button_    (0),
        get_value_        (b),
        set_value_        (c),
        editable_         (f),
        immediate_        (g)
    {
      TRACE("hugh:gtkmm::radio_button_input<" + support::demangle(typeid(T)) +
            ">::radio_button_input");
      
      if (!a.empty()) {
        label_.set_justify    (Gtk::JUSTIFY_LEFT);
        label_.set_width_chars(label_.get_text().length());

        if (!d.empty()) {
          label_.set_tooltip_markup(d);
        }
      }
      
      Gtk::RadioButton::Group grp;
      
      for (unsigned i(0); i < e.size(); ++i) {
        radio_buttons_.push_back(Gtk::manage(new Gtk::RadioButton(e[i])));

        if (0 == i) {
          grp = radio_buttons_[0]->get_group();
        } else {
          radio_buttons_[i]->set_group(grp);
        }

        if (!d.empty()) {
          radio_buttons_[i]->set_tooltip_markup(d);
        }
        
        radio_buttons_[i]->signal_clicked().
          connect(sigc::bind<1>(sigc::mem_fun(this,
                                              &radio_button_input<T>::on_button_activate), i));
      }
      
      radio_buttons_[active_button_ = get_value_()]->set_active();

      for (auto& rb : radio_buttons_) {
        rb->set_sensitive(editable_);
      }
    }
    
    template <typename T>
    inline void
    radio_button_input<T>::on_button_activate(unsigned which) 
    {
      TRACE("hugh:gtkmm::radio_button_input<" + support::demangle(typeid(T)) +
            ">::on_button_activate");
      
      active_button_ = which;

      if (editable_ && immediate_ && (get_value_() != static_cast<T>(active_button_))) {
        set_value_(static_cast<T>(active_button_));
      }
    }

    template <typename T>
    inline /* explicit */
    hradio_button_input<T>::hradio_button_input(std::string const&              a,
                                                get_value_function_type         b,
                                                set_value_function_type         c,
                                                std::string const&              d,
                                                std::vector<std::string> const& e,
                                                bool                            f,
                                                bool                            g)
      : Gtk::HBox    (),
        inherited_rbi(a, b, c, d, e, f, g)
    {
      TRACE("hugh:gtkmm::hradio_button_input<" + support::demangle(typeid(T)) +
            ">::hradio_button_input");
      
      set_border_width(1);

      if (!inherited_rbi::label_.get_text().empty()) {
        inherited_rbi::label_.set_alignment(Gtk::ALIGN_END, Gtk::ALIGN_CENTER);

        pack_start(inherited_rbi::label_, Gtk::PACK_SHRINK);
      }
      
      for (auto const& rb : inherited_rbi::radio_buttons_) {
        pack_start(*rb, Gtk::PACK_SHRINK);
      }
    }

    template <typename T>
    inline /* explicit */
    vradio_button_input<T>::vradio_button_input(std::string const&              a,
                                                get_value_function_type         b,
                                                set_value_function_type         c,
                                                std::string const&              d,
                                                std::vector<std::string> const& e,
                                                bool                            f,
                                                bool                            g)
      : Gtk::VBox    (),
        inherited_rbi(a, b, c, d, e, f, g)
    {
      TRACE("hugh:gtkmm::vradio_button_input<" + support::demangle(typeid(T)) +
            ">::vradio_button_input");
      
      set_border_width(1);

      if (!inherited_rbi::label_.get_text().empty()) {
        inherited_rbi::label_.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

        pack_start(inherited_rbi::label_, Gtk::PACK_SHRINK);
      }
      
      for (auto const& rb : inherited_rbi::radio_buttons_) {
        pack_start(*rb, Gtk::PACK_SHRINK);
      }
    }
    
  } // namespace gtkmm {
  
} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_APP_GTKMM_RADIO_BUTTON_INPUT_INL)
