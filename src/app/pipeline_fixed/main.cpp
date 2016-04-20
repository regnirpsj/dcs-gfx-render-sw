// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  pipeline_fixed/main.cpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <cstdlib> // EXIT_SUCCESS
#include <memory>  // std::unique_ptr<>

// includes, project

#include <hugh/platform/posix/application/base.hpp>

#include <gtkmm_wrap/application.hpp>
#include <gtkmm_wrap/window.hpp>

#define HUGH_USE_TRACE
//#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>


namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  class app : public hugh::platform::posix::application::base,
              public hugh::gtkmm::application {
    
  public:

    using command_line      = hugh::platform::application::command_line;
    using gtkmm_application = hugh::gtkmm::application;
    using posix_application = hugh::platform::posix::application::base;
    
    explicit app(command_line const& a)
      : posix_application(a),
        gtkmm_application(),
        win_             (new hugh::gtkmm::window)
    {
      TRACE("<unnamed>::app::app");
    }

    virtual signed run()
    {
      TRACE("<unnamed>::app::run");
      
      return hugh::gtkmm::application::run(*win_);
    }

  private:
    
    std::unique_ptr<hugh::gtkmm::window> win_;
    
  };
  
  // variables, internal
  
  // functions, internal

} // namespace {

int
main(int argc, char const* argv[])
{
  TRACE("main");

  using namespace hugh::platform::application;
  
  return execute<app>(command_line(argc, argv), std::nothrow);
}
