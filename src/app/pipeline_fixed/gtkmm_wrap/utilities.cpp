// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/application.cpp                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "gtkmm_wrap/utilities.hpp"

// includes, system

//#include <>

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {

  namespace gtkmm {
    
    // variables, exported
  
    // functions, exported

    Gtk::VBox*
    empty_label_in_vbox(std::string const& text)
    {
      TRACE("hugh::gtkmm::empty_label_in_vbox");

      Gtk::VBox* vbox(Gtk::manage(new Gtk::VBox));

      vbox->set_border_width(3);
      vbox->set_spacing     (1);

      {
        Gtk::Label* label(Gtk::manage(new Gtk::Label("<small> </small>", Gtk::ALIGN_START)));

        label->set_justify   (Gtk::JUSTIFY_LEFT);
        label->set_use_markup(true);

        vbox->pack_start(*label, Gtk::PACK_SHRINK);
      }

      {
        Gtk::Label* label(Gtk::manage(new Gtk::Label(" " + text, Gtk::ALIGN_START)));

        label->set_justify   (Gtk::JUSTIFY_LEFT);
        label->set_use_markup(true);

        vbox->pack_start(*label, Gtk::PACK_SHRINK);
      }

      {
        Gtk::Label* label(Gtk::manage(new Gtk::Label("<small> </small>", Gtk::ALIGN_START)));

        label->set_justify   (Gtk::JUSTIFY_LEFT);
        label->set_use_markup(true);

        vbox->pack_start(*label, Gtk::PACK_SHRINK);
      }

      return vbox;
    }

    Gtk::Frame*
    empty_label_in_framed_vbox(std::string const& title, std::string const& text)
    {
      TRACE("hugh::gtkmm::empty_label_in_framed_vbox");

      Gtk::Frame* frame(Gtk::manage(new Gtk::Frame(title)));

      frame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
      frame->add            (*empty_label_in_vbox(text));

      return frame;
    }

  } // namespace gtkmm {
  
} // namespace hugh {
