# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

if(VERBOSE)
  message(STATUS "Loading ${PROJECT_NAME} options")
endif()

include(CMakeAddons_SetupOptions)

# tracing
option(HUGH_TRACE_ALL "Enable runtime function tracing for everything!" OFF)
