# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(GLM  ${GLM_MINIMUM_VERSION} REQUIRED)
find_package(HUGH                        REQUIRED COMPONENTS glm scene support)

include_directories(SYSTEM ${GLM_INCLUDE_DIR})
include_directories(SYSTEM ${HUGH_INCLUDE_DIRS})

set(SRC)
list(APPEND SRC pipeline.cpp)

set(LIBS)
list(APPEND LIBS ${HUGH_LIBRARIES})

set(LIB "common")

cma_setup_library(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS} STATIC NOINSTALL)
