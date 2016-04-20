// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/window.cpp                                                       */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "gtkmm_wrap/window.hpp"

// includes, system

#include <gdk/gdkkeysyms.h> // GDK_*

// includes, project

//#include <>

#if defined(HUGH_GTKMM_TRACE)
#  define HUGH_USE_TRACE
#endif
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
    window::window()
      : inherited()
    {
      TRACE("hugh::gtkmm::window::window");

      {
        static Gdk::EventMask const event_mask(Gdk::EXPOSURE_MASK          |
                                               Gdk::VISIBILITY_NOTIFY_MASK |
                                               Gdk::BUTTON_MOTION_MASK     |
                                               Gdk::BUTTON_PRESS_MASK      |
                                               Gdk::BUTTON_RELEASE_MASK    |
                                               Gdk::KEY_PRESS_MASK         |
                                               Gdk::KEY_RELEASE_MASK       |
                                               Gdk::POINTER_MOTION_MASK    |
                                               Gdk::SCROLL_MASK            );

        set_events(get_events() | event_mask);
      }
    }

    /* virtual */
    window::~window()
    {
      TRACE("hugh::gtkmm::window::~window");
    }

    /* virtual */ void
    window::on_set_focus(Gtk::Widget* a)
    {
      TRACE("hugh::gtkmm::window::on_set_focus");

      inherited::on_set_focus(a);
    }

    /* virtual */ void
    window::on_add(Gtk::Widget* a)
    {
      TRACE("hugh::gtkmm::window::on_add");

      inherited::on_add(a);
    }

    /* virtual */ void
    window::on_remove(Gtk::Widget* a)
    {
      TRACE("hugh::gtkmm::window::on_remove");

      inherited::on_remove(a);
    }

    /* virtual */ void
    window::on_check_resize()
    {
      TRACE("hugh::gtkmm::window::on_check_resize");

      inherited::on_check_resize();
    }

    /* virtual */ void
    window::on_set_focus_child(Gtk::Widget* a)
    {
      TRACE("hugh::gtkmm::window::on_set_focus_child");

      inherited::on_set_focus_child(a);
    }

    /* virtual */ void
    window::on_show()
    {
      TRACE("hugh::gtkmm::window::on_show");

      inherited::on_show();
    }

    /* virtual */ void
    window::on_hide()
    {
      TRACE("hugh::gtkmm::window::on_hide");

      inherited::on_hide();
    }

    /* virtual */ void
    window::on_map()
    {
      TRACE("hugh::gtkmm::window::on_map");

      inherited::on_map();
    }

    /* virtual */ void
    window::on_unmap()
    {
      TRACE("hugh::gtkmm::window::on_unmap");

      inherited::on_unmap();
    }

    /* virtual */ void
    window::on_realize()
    {
      TRACE("hugh::gtkmm::window::on_realize");

      inherited::on_realize();
    }

    /* virtual */ void
    window::on_unrealize()
    {
      TRACE("hugh::gtkmm::window::on_unrealize");

      inherited::on_unrealize();
    }

    /* virtual */ void
    window::on_size_allocate(Gtk::Allocation& a)
    {
      TRACE("hugh::gtkmm::window::on_size_allocate");

      inherited::on_size_allocate(a);
    }
    
    /* virtual */ void
    window::on_state_changed(Gtk::StateType a)
    {
      TRACE("hugh::gtkmm::window::on_state_changed");

      inherited::on_state_changed(a);
    }
    
    /* virtual */ void
    window::on_parent_changed(Widget* a)
    {
      TRACE("hugh::gtkmm::window::on_parent_changed");

      inherited::on_parent_changed(a);
    }
    
    /* virtual */ void
    window::on_hierarchy_changed(Widget* a)
    {
      TRACE("hugh::gtkmm::window::on_hierarchy_changed");

      inherited::on_hierarchy_changed(a);
    }
    
    /* virtual */ void
    window::on_style_updated()
    {
      TRACE("hugh::gtkmm::window::on_style_updated");

      inherited::on_style_updated();
    }
    
    /* virtual */ void
    window::on_direction_changed(Gtk::TextDirection a)
    {
      TRACE("hugh::gtkmm::window::on_direction_changed");

      inherited::on_direction_changed(a);
    }
    
    /* virtual */ void
    window::on_grab_notify(bool a)
    {
      TRACE("hugh::gtkmm::window::on_grab_notify");

      inherited::on_grab_notify(a);
    }
    
    /* virtual */ void
    window::on_child_notify(GParamSpec* a)
    {
      TRACE("hugh::gtkmm::window::on_child_notify");

      inherited::on_child_notify(a);
    }
    
    /* virtual */ bool
    window::on_mnemonic_activate(bool a)
    {
      TRACE("hugh::gtkmm::window::on_mnemonic_activate");

      return inherited::on_mnemonic_activate(a);
    }
    
    /* virtual */ void
    window::on_grab_focus()
    {
      TRACE("hugh::gtkmm::window::on_grab_focus");

      inherited::on_grab_focus();
    }
    
    /* virtual */ bool
    window::on_focus(Gtk::DirectionType a)
    {
      TRACE("hugh::gtkmm::window::on_focus");

      return inherited::on_focus(a);
    }
 
    /* virtual */ bool
    window::on_event(GdkEvent* a)
    {
      TRACE("hugh::gtkmm::window::on_event");

      return inherited::on_event(a);
    }
    
    /* virtual */ bool
    window::on_button_press_event(GdkEventButton* a)
    {
      TRACE("hugh::gtkmm::window::on_button_press_event");

      return inherited::on_button_press_event(a);
    }
    
    /* virtual */ bool
    window::on_button_release_event(GdkEventButton* a)
    {
      TRACE("hugh::gtkmm::window::on_button_release_event");

      return inherited::on_button_release_event(a);
    }
    
    /* virtual */ bool
    window::on_scroll_event(GdkEventScroll* a)
    {
      TRACE("hugh::gtkmm::window::on_scroll_event");

      return inherited::on_scroll_event(a);
    }
    
    /* virtual */ bool
    window::on_motion_notify_event(GdkEventMotion* a)
    {
      TRACE("hugh::gtkmm::window::on_motion_notify_event");

      return inherited::on_motion_notify_event(a);
    }
    
    /* virtual */ bool
    window::on_delete_event(GdkEventAny* a)
    {
      TRACE("hugh::gtkmm::window::on_delete_event");

      return inherited::on_delete_event(a);
    }
    
    /* virtual */ bool
    window::on_draw(::Cairo::RefPtr<::Cairo::Context> const& a)
    {
      TRACE("hugh::gtkmm::window::on_draw");

      return inherited::on_draw(a);
    }
    
    /* virtual */ bool
    window::on_key_press_event(GdkEventKey* a)
    {
      TRACE("hugh::gtkmm::window::on_key_press_event");

      return inherited::on_key_press_event(a);
    }
    
    /* virtual */ bool
    window::on_key_release_event(GdkEventKey* a)
    {
      TRACE("hugh::gtkmm::window::on_key_release_event");

      return inherited::on_key_release_event(a);
    }
    
    /* virtual */ bool
    window::on_enter_notify_event(GdkEventCrossing* a)
    {
      TRACE("hugh::gtkmm::window::on_enter_notify_event");

      return inherited::on_enter_notify_event(a);
    }
    
    /* virtual */ bool
    window::on_leave_notify_event(GdkEventCrossing* a)
    {
      TRACE("hugh::gtkmm::window::on_leave_notify_event");

      return inherited::on_leave_notify_event(a);
    }
    
    /* virtual */ bool
    window::on_configure_event(GdkEventConfigure* a)
    {
      TRACE("hugh::gtkmm::window::on_configure_event");

      return inherited::on_configure_event(a);
    }
    
    /* virtual */ bool
    window::on_focus_in_event(GdkEventFocus* a)
    {
      TRACE("hugh::gtkmm::window::on_focus_in_event");

      return inherited::on_focus_in_event(a);
    }
    
    /* virtual */ bool
    window::on_focus_out_event(GdkEventFocus* a)
    {
      TRACE("hugh::gtkmm::window::on_focus_out_event");

      return inherited::on_focus_out_event(a);
    }
    
    /* virtual */ bool
    window::on_map_event(GdkEventAny* a)
    {
      TRACE("hugh::gtkmm::window::on_map_event");

      return inherited::on_map_event(a);
    }
    
    /* virtual */ bool
    window::on_unmap_event(GdkEventAny* a)
    {
      TRACE("hugh::gtkmm::window::on_unmap_event");

      return inherited::on_unmap_event(a);
    }
    
    /* virtual */ bool
    window::on_property_notify_event(GdkEventProperty* a)
    {
      TRACE("hugh::gtkmm::window::on_property_notify_event");

      return inherited::on_property_notify_event(a);
    }
    
    /* virtual */ bool
    window::on_selection_clear_event(GdkEventSelection* a)
    {
      TRACE("hugh::gtkmm::window::on_selection_clear_event");

      return inherited::on_selection_clear_event(a);
    }
    
    /* virtual */ bool
    window::on_selection_request_event(GdkEventSelection* a)
    {
      TRACE("hugh::gtkmm::window::on_selection_request_event");

      return inherited::on_selection_request_event(a);
    }
    
    /* virtual */ bool
    window::on_selection_notify_event(GdkEventSelection* a)
    {
      TRACE("hugh::gtkmm::window::on_selection_notify_event");

      return inherited::on_selection_notify_event(a);
    }
    
    /* virtual */ bool
    window::on_proximity_in_event(GdkEventProximity* a)
    {
      TRACE("hugh::gtkmm::window::on_proximity_in_event");

      return inherited::on_proximity_in_event(a);
    }
    
    /* virtual */ bool
    window::on_proximity_out_event(GdkEventProximity* a)
    {
      TRACE("hugh::gtkmm::window::on_proximity_out_event");

      return inherited::on_proximity_out_event(a);
    }
 
    /* virtual */ bool
    window::on_visibility_notify_event(GdkEventVisibility* a)
    {
      TRACE("hugh::gtkmm::window::on_visibility_notify_event");

      return inherited::on_visibility_notify_event(a);
    }
    
    /* virtual */ bool
    window::on_window_state_event(GdkEventWindowState* a)
    {
      TRACE("hugh::gtkmm::window::on_window_state_event");

      return inherited::on_window_state_event(a);
    }
    
    /* virtual */ void
    window::on_selection_get(Gtk::SelectionData& a, guint b, guint c)
    {
      TRACE("hugh::gtkmm::window::on_selection_get");

      inherited::on_selection_get(a, b, c);
    }
    
    /* virtual */ void
    window::on_selection_received(Gtk::SelectionData const& a, guint b)
    {
      TRACE("hugh::gtkmm::window::on_selection_received");

      inherited::on_selection_received(a, b);
    }
    
    /* virtual */ void
    window::on_drag_begin(Glib::RefPtr<Gdk::DragContext> const& a)
    {
      TRACE("hugh::gtkmm::window::on_drag_begin");

      inherited::on_drag_begin(a);
    }
    
    /* virtual */ void
    window::on_drag_end(Glib::RefPtr<Gdk::DragContext> const& a)
    {
      TRACE("hugh::gtkmm::window::on_drag_end");

      inherited::on_drag_end(a);
    }
    
    /* virtual */ void
    window::on_drag_data_get(Glib::RefPtr<Gdk::DragContext> const& a, Gtk::SelectionData& b,
                             guint c, guint d)
    {
      TRACE("hugh::gtkmm::window::on_drag_data_get");

      inherited::on_drag_data_get(a, b, c, d);
    }
    
    /* virtual */ void
    window::on_drag_data_delete(Glib::RefPtr<Gdk::DragContext> const& a)
    {
      TRACE("hugh::gtkmm::window::on_drag_data_delete");

      inherited::on_drag_data_delete(a);
    }
    
    /* virtual */ void
    window::on_drag_leave(Glib::RefPtr<Gdk::DragContext> const& a, guint b)
    {
      TRACE("hugh::gtkmm::window::on_drag_leave");

      inherited::on_drag_leave(a, b);
    }
    
    /* virtual */ bool
    window::on_drag_motion(Glib::RefPtr<Gdk::DragContext> const& a, int b, int c, guint d)
    {
      TRACE("hugh::gtkmm::window::on_drag_motion");

      return inherited::on_drag_motion(a, b, c, d);
    }
    
    /* virtual */ bool
    window::on_drag_drop(Glib::RefPtr<Gdk::DragContext> const& a, int b, int c, guint d)
    {
      TRACE("hugh::gtkmm::window::on_drag_drop");

      return inherited::on_drag_drop(a, b, c, d);
    }

    /* virtual */ void
    window::on_screen_changed(Glib::RefPtr<Gdk::Screen> const& a)
    {
      TRACE("hugh::gtkmm::window::on_screen_changed");

      inherited::on_screen_changed(a);
    }

  } // namespace gtkmm {
  
} // namespace hugh {
