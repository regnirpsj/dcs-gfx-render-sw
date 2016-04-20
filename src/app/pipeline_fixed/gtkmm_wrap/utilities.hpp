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

#include <gtkmm.h> // Gtk::*

// includes, project

// #include <>

namespace hugh {

  namespace gtkmm {
    
    // types, exported (class, enum, struct, union, typedef)
    
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

    Gtk::VBox*  empty_label_in_vbox       (std::string const& /* text  */);
    Gtk::Frame* empty_label_in_framed_vbox(std::string const& /* title */ ,
                                           std::string const& /* text  */);
    
  } // namespace gtkmm {
  
} // namespace hugh {

#endif // #if !defined(HUGH_APP_GTKMM_UTILITIES_HPP)
