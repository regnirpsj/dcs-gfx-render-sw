// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/window.hpp                                                       */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_WINDOW_HPP)

#define HUGH_APP_GTKMM_WINDOW_HPP

// includes, system

#include <gtkmm/window.h> // Gtk::Window

// includes, project

// #include <>

namespace hugh {

  namespace gtkmm {
    
    // types, exported (class, enum, struct, union, typedef)

    class window : public Gtk::Window {

    public:

      using inherited = Gtk::Window;

      explicit window();
      virtual ~window();
    
    protected:

      virtual void on_set_focus(Gtk::Widget*);
      virtual void on_add(Gtk::Widget*);
      virtual void on_remove(Gtk::Widget*);
      virtual void on_check_resize();
      virtual void on_set_focus_child(Gtk::Widget*);
      virtual void on_show();
      virtual void on_hide();
      virtual void on_map();
      virtual void on_unmap();
      virtual void on_realize();
      virtual void on_unrealize();
      virtual void on_size_allocate(Gtk::Allocation&);
      virtual void on_state_changed(Gtk::StateType);
      virtual void on_parent_changed(Widget*);
      virtual void on_hierarchy_changed(Widget*);
      virtual void on_style_updated();
      virtual void on_direction_changed(Gtk::TextDirection);
      virtual void on_grab_notify(bool);
      virtual void on_child_notify(GParamSpec*);
      virtual bool on_mnemonic_activate(bool);
      virtual void on_grab_focus();
      virtual bool on_focus(Gtk::DirectionType);
      virtual bool on_event(GdkEvent*);
      virtual bool on_button_press_event(GdkEventButton*);
      virtual bool on_button_release_event(GdkEventButton*);
      virtual bool on_scroll_event(GdkEventScroll*);
      virtual bool on_motion_notify_event(GdkEventMotion*);
      virtual bool on_delete_event(GdkEventAny*);
      virtual bool on_draw(::Cairo::RefPtr<::Cairo::Context> const&);
      virtual bool on_key_press_event(GdkEventKey*);
      virtual bool on_key_release_event(GdkEventKey*);
      virtual bool on_enter_notify_event(GdkEventCrossing*);
      virtual bool on_leave_notify_event(GdkEventCrossing*);
      virtual bool on_configure_event(GdkEventConfigure*);
      virtual bool on_focus_in_event(GdkEventFocus*);
      virtual bool on_focus_out_event(GdkEventFocus*);
      virtual bool on_map_event(GdkEventAny*);
      virtual bool on_unmap_event(GdkEventAny*);
      virtual bool on_property_notify_event(GdkEventProperty*);
      virtual bool on_selection_clear_event(GdkEventSelection*);
      virtual bool on_selection_request_event(GdkEventSelection*);
      virtual bool on_selection_notify_event(GdkEventSelection*);
      virtual bool on_proximity_in_event(GdkEventProximity*);
      virtual bool on_proximity_out_event(GdkEventProximity*);
      virtual bool on_visibility_notify_event(GdkEventVisibility*);
      virtual bool on_window_state_event(GdkEventWindowState*);
      virtual void on_selection_get(Gtk::SelectionData&, guint, guint);
      virtual void on_selection_received(Gtk::SelectionData const&, guint);
      virtual void on_drag_begin(Glib::RefPtr<Gdk::DragContext> const&);
      virtual void on_drag_end(Glib::RefPtr<Gdk::DragContext> const&);
      virtual void on_drag_data_get(Glib::RefPtr<Gdk::DragContext> const&, Gtk::SelectionData&,
                                    guint, guint);
      virtual void on_drag_data_delete(Glib::RefPtr<Gdk::DragContext> const&);
      virtual void on_drag_leave(Glib::RefPtr<Gdk::DragContext> const&, guint);
      virtual bool on_drag_motion(Glib::RefPtr<Gdk::DragContext> const&, int, int, guint);
      virtual bool on_drag_drop(Glib::RefPtr<Gdk::DragContext> const&, int, int, guint);
      virtual void on_screen_changed(Glib::RefPtr<Gdk::Screen> const&);
    
    };

    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

  } // namespace gtkmm {
  
} // namespace hugh {

#endif // #if !defined(HUGH_APP_GTKMM_WINDOW_HPP)
