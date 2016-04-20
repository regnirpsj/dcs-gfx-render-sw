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

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS program_options)
find_package(GLM   ${GLM_MINIMUM_VERSION}   REQUIRED)
find_package(HUGH                           REQUIRED COMPONENTS glm platform platform_posix scene support)

include_directories(SYSTEM ${Boost_INCLUDE_DIR})
include_directories(SYSTEM ${GLM_INCLUDE_DIR})
include_directories(SYSTEM ${GTKMM_INCLUDE_DIRS})
include_directories(SYSTEM ${HUGH_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SRC)
list(APPEND SRC main.cpp)
list(APPEND SRC window_buffer.cpp)
list(APPEND SRC window_control.cpp)

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS hugh_render_software)
list(APPEND LIBS gtkmm_wrap)
list(APPEND LIBS ${HUGH_LIBRARIES})
list(APPEND LIBS ${GTKMM_LIBRARIES})
list(APPEND LIBS ${Boost_LIBRARIES})

set(APP "pipeline_fixed")

cma_setup_application(${APP} SOURCES ${SRC} DEPENDENCIES ${LIBS})

add_subdirectory(gtkmm_wrap)
