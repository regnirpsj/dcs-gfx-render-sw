# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS unit_test_framework)

include_directories(SYSTEM ${Boost_INLCUDE_DIR})

set(SRC)
list(APPEND SRC attribute.cpp)
list(APPEND SRC fragment.cpp)
list(APPEND SRC line.cpp)
list(APPEND SRC triangle.cpp)
list(APPEND SRC pipeline_fixed.cpp)
list(APPEND SRC primitive_lines.cpp)
list(APPEND SRC primitive_points.cpp)
list(APPEND SRC primitive_triangles.cpp)
list(APPEND SRC rasterizer_simple.cpp)

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS ${LIB})
list(APPEND LIBS ${Boost_LIBRARIES})

cma_setup_test(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS})
