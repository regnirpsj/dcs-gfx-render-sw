// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/application.hpp                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_APPLICATION_HPP)

#define HUGH_APP_GTKMM_APPLICATION_HPP

// includes, system

#include <gtkmm/application.h> // Gtk::Application

// includes, project

// #include <>

namespace hugh {

  namespace gtkmm {
    
    // types, exported (class, enum, struct, union, typedef)

    class application : public Gtk::Application {

    public:

      using inherited = Gtk::Application;

      explicit application();
      explicit application(int /* argc */, char* /* argv */[]);
      virtual ~application();
    
    protected:
    
      virtual void on_window_added(Gtk::Window*);
      virtual void on_window_removed(Gtk::Window*);
      virtual void on_open(type_vec_files const&, Glib::ustring const&);
      virtual void on_startup();
      virtual void on_activate();
      virtual int  on_command_line(Glib::RefPtr<Gio::ApplicationCommandLine> const&);
      virtual void on_action_added(Glib::ustring const&);
      virtual void on_action_enabled_changed(Glib::ustring const&, bool);
      virtual void on_action_removed(Glib::ustring const&);
      virtual void on_action_state_changed(Glib::ustring const&, Glib::VariantBase const&);
    
    };
    
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

  } // namespace gtkmm {
  
} // namespace hugh {

#endif // #if !defined(HUGH_APP_GTKMM_APPLICATION_HPP)
