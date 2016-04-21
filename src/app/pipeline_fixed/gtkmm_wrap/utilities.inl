// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/utilities.inl                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_UTILITIES_INL)

#define HUGH_APP_GTKMM_UTILITIES_INL

// includes, system

//#include <>

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
//#if defined(HUGH_USE_TRACE) || defined(HUGH_ALL_TRACE)
//#  include <typeinfo>
//#  include <hugh/support/type_info.hpp>
//#endif

namespace hugh {

  namespace gtkmm {
    
    // functions, inlined (inline)
  
    template <typename BoxType, typename ContainerType>
    inline BoxType*
    pack_items_in_box(ContainerType const& widgets, unsigned bwidth)
    {
      BoxType* result(Gtk::manage(new BoxType));
    
      result->set_border_width(bwidth);
      result->set_spacing     (bwidth);
    
      for (unsigned i(0); i < widgets.size(); ++i) {
        result->pack_start(*widgets[i], Gtk::PACK_SHRINK);
      }
    
      return result;
    }
  
    template <typename ContainerType>
    inline Gtk::HBox*
    pack_items_in_hbox(ContainerType const& widgets, unsigned bwidth)
    {
      return pack_items_in_box<Gtk::HBox>(widgets, bwidth);
    }
  
    template <unsigned N>
    inline Gtk::HBox*
    pack_items_in_hbox(std::array<Gtk::Widget*, N> const& widgets, unsigned bwidth)
    {
      return pack_items_in_box<Gtk::HBox>(std::vector<Gtk::Widget*>(widgets.begin(),
                                                                    widgets.end  ()),
                                          bwidth);
    }

    template <unsigned N>
    inline Gtk::Frame*
    pack_items_in_framed_hbox(std::string const& title, std::array<Gtk::Widget*, N> const& widgets,
                              unsigned bwidth)
    {
      Gtk::Frame* frame(Gtk::manage(new Gtk::Frame(title)));

      frame->add(*pack_items_in_box<Gtk::HBox>(std::vector<Gtk::Widget*>(widgets.begin(),
                                                                         widgets.end  ()),
                                               bwidth));
      
      return frame;
    }

    template <typename ContainerType>
    inline Gtk::VBox*
    pack_items_in_vbox(ContainerType const& widgets, unsigned bwidth)
    {
      return pack_items_in_box<Gtk::VBox>(widgets, bwidth);
    }
  
    template <unsigned N>
    inline Gtk::VBox*
    pack_items_in_vbox(std::array<Gtk::Widget*, N> const& widgets, unsigned bwidth)
    {
      return pack_items_in_box<Gtk::VBox>(std::vector<Gtk::Widget*>(widgets.begin(),
                                                                    widgets.end  ()),
                                          bwidth);
    }

    template <unsigned N>
    inline Gtk::Frame*
    pack_items_in_framed_vbox(std::string const& title, std::array<Gtk::Widget*, N> const& widgets,
                              unsigned bwidth)
    {
      Gtk::Frame* frame(Gtk::manage(new Gtk::Frame(title)));

      frame->add(*pack_items_in_box<Gtk::VBox>(std::vector<Gtk::Widget*>(widgets.begin(),
                                                                         widgets.end  ()),
                                               bwidth));
      
      return frame;
    }
    
  } // namespace gtkmm {
  
} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_APP_GTKMM_UTILITIES_INL)
