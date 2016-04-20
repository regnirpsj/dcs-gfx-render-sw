# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

if(NOT GTKMM_FOUND)
  return()
endif()

find_package(HUGH REQUIRED COMPONENTS support)

include_directories(SYSTEM ${GTKMM_INCLUDE_DIRS})
include_directories(SYSTEM ${HUGH_INCLUDE_DIRS})

#add_definitions(-DHUGH_ALL_TRACE)

set(SRC)
list(APPEND SRC application.cpp)
list(APPEND SRC utilities.cpp)
list(APPEND SRC window.cpp)

set(LIBS)
list(APPEND LIBS ${HUGH_LIBRARIES})
list(APPEND LIBS ${GTKMM_LIBRARIES})

cma_setup_library(gtkmm_wrap SOURCES ${SRC} DEPENDENCIES ${LIBS} STATIC NOINSTALL)
