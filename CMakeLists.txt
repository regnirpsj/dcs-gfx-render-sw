# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(HUGH_RENDER_SW VERSION 0.1.0)

if(DEFINED ENV{HUGH_INSTALL_PREFIX})
  get_filename_component(dir $ENV{HUGH_INSTALL_PREFIX} ABSOLUTE BASE_DIR ${CMAKE_BINARY_DIR})
  set(HUGH_INSTALL_PREFIX ${dir} CACHE INTERNAL "HUGH Installation Root")
endif()

list(APPEND CMAKE_MODULE_PATH ${HUGH_INSTALL_PREFIX}/share/hugh/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(CheckOutOfTreeBuild)
include(SetupInitialCache)
include(SetupBuildType)
include(SetupInstallPrefix)
include(SetupPlatformAndArchitecture)
include(SetupFunctionsAndMacros)

cma_print_current_directory()

include(SetupCompilerDefaults)
include(SetupProjectDefaults)
include(SetupUnitTests)

include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_BINARY_DIR}/exports)

add_subdirectory(share)
add_subdirectory(src)

include(ShowConfigSummary)
# keep last
include(SetupPackaging)
