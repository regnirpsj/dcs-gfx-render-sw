// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/app/gtkmm/utilities.hpp                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_APP_GTKMM_UTILITIES_HPP)

#define HUGH_APP_GTKMM_UTILITIES_HPP

// includes, system

#include <array>         // std::array<>
#include <gtkmm/box.h>   // Gtk::[H|V]Box
#include <gtkmm/frame.h> // Gtk::Frame

// includes, project

// #include <>

namespace hugh {

  namespace gtkmm {
    
    // types, exported (class, enum, struct, union, typedef)
    
    // variables, exported (extern)

    // functions, inlined (inline)

    template <typename BoxType, typename ContainerType>
    BoxType*    pack_items_in_box        (ContainerType const&,               unsigned = 2);
    
    template <typename ContainerType>
    Gtk::HBox*  pack_items_in_hbox       (ContainerType const&,               unsigned = 2);
    template <unsigned N>
    Gtk::HBox*  pack_items_in_hbox       (std::array<Gtk::Widget*, N> const&, unsigned = 2);
    template <unsigned N>
    Gtk::Frame* pack_items_in_framed_hbox(std::string const&,
                                          std::array<Gtk::Widget*, N> const&, unsigned = 2);
    
    template <typename ContainerType>
    Gtk::VBox*  pack_items_in_vbox       (ContainerType const&,               unsigned = 2);
    template <unsigned N>
    Gtk::VBox*  pack_items_in_vbox       (std::array<Gtk::Widget*, N> const&, unsigned = 2);
    template <unsigned N>
    Gtk::Frame* pack_items_in_framed_vbox(std::string const&,
                                          std::array<Gtk::Widget*, N> const&, unsigned = 2);
    
    // functions, exported (extern)

    Gtk::VBox*  empty_label_in_vbox       (std::string const& /* text  */);
    Gtk::Frame* empty_label_in_framed_vbox(std::string const& /* title */ ,
                                           std::string const& /* text  */);
    
  } // namespace gtkmm {
  
} // namespace hugh {

#include <gtkmm_wrap/utilities.inl>

#endif // #if !defined(HUGH_APP_GTKMM_UTILITIES_HPP)
