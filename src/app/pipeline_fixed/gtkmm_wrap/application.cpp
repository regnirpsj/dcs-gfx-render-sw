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

#include "gtkmm_wrap/application.hpp"

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

    /* explicit */
    application::application()
      : inherited()
    {
      TRACE("hugh::gtkmm::application::application");
    }
    
    /* explicit */
    application::application(int a, char* b[])
      // actually, param3 and param4 have defaults but it looks like not all
      // gtkmm3 installations got that memo 8(
      : inherited(a, b, Glib::ustring(), Gio::APPLICATION_FLAGS_NONE)
    {
      TRACE("hugh::gtkmm::application::application");
    }

    /* virtual */
    application::~application()
    {
      TRACE("hugh::gtkmm::application::~application");
    }
    
    /* virtual */ void
    application::on_window_added(Gtk::Window* a)
    {
      TRACE("hugh::gtkmm::application::on_window_added");

      inherited::on_window_added(a);
    }
    
    /* virtual */ void
    application::on_window_removed(Gtk::Window* a)
    {
      TRACE("hugh::gtkmm::application::on_window_removed");

      inherited::on_window_removed(a);
    }

    /* virtual */ void
    application::on_open(type_vec_files const& a, Glib::ustring const& b)
    {
      TRACE("hugh::gtkmm::application::on_open");

      inherited::on_open(a, b);
    }

    /* virtual */ void
    application::on_startup()
    {
      TRACE("hugh::gtkmm::application::on_startup");

      inherited::on_startup();
    }
    
    /* virtual */ void
    application::on_activate()
    {
      TRACE("hugh::gtkmm::application::on_activate");

      inherited::on_activate();
    }
    
    /* virtual */ int
    application::on_command_line(Glib::RefPtr<Gio::ApplicationCommandLine> const& a)
    {
      TRACE("hugh::gtkmm::application::on_command_line");

      return inherited::on_command_line(a);
    }

    /* virtual */ void
    application::on_action_added(Glib::ustring const& a)
    {
      TRACE("hugh::gtkmm::application::on_action_added");

      inherited::on_action_added(a);
    }
    
    /* virtual */ void
    application::on_action_enabled_changed(Glib::ustring const& a, bool b)
    {
      TRACE("hugh::gtkmm::application::on_action_enabled_changed");

      inherited::on_action_enabled_changed(a, b);
    }
    
    /* virtual */ void
    application::on_action_removed(Glib::ustring const& a)
    {
      TRACE("hugh::gtkmm::application::on_action_removed");

      inherited::on_action_removed(a);
    }
    
    /* virtual */ void
    application::on_action_state_changed(Glib::ustring const& a, Glib::VariantBase const& b)
    {
      TRACE("hugh::gtkmm::application::on_action_state_changed");

      inherited::on_action_state_changed(a, b);
    }

  } // namespace gtkmm {
  
} // namespace hugh {
