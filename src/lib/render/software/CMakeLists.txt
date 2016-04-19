# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED)
find_package(GLM   ${GLM_MINIMUM_VERSION}   REQUIRED)
find_package(HUGH                           REQUIRED COMPONENTS field glm scene support)

include_directories(SYSTEM ${Boost_INCLUDE_DIR})
include_directories(SYSTEM ${GLM_INCLUDE_DIR})
include_directories(SYSTEM ${HUGH_INCLUDE_DIRS})

set(SRC)
list(APPEND SRC attribute.cpp)
list(APPEND SRC context.cpp)
list(APPEND SRC fragment.cpp)
list(APPEND SRC line.cpp)
list(APPEND SRC triangle.cpp)
list(APPEND SRC vertex.cpp)

list(APPEND SRC buffer/base.cpp)
list(APPEND SRC buffer/color.cpp)
list(APPEND SRC buffer/depth.cpp)

list(APPEND SRC pipeline/base.cpp)
list(APPEND SRC pipeline/fixed/base.cpp)
list(APPEND SRC pipeline/fixed/direct3d.cpp)
list(APPEND SRC pipeline/fixed/opengl.cpp)
#list(APPEND SRC pipeline/flexible.cpp)

list(APPEND SRC primitive/base.cpp)
list(APPEND SRC primitive/line_list.cpp)
#list(APPEND SRC primitive/line_loop.cpp)
list(APPEND SRC primitive/line_strip.cpp)
list(APPEND SRC primitive/point_list.cpp)
#list(APPEND SRC primitive/triangle_fan.cpp)
list(APPEND SRC primitive/triangle_list.cpp)
list(APPEND SRC primitive/triangle_strip.cpp)

list(APPEND SRC rasterizer/base.cpp)
list(APPEND SRC rasterizer/simple.cpp)

#list(APPEND SRC shader/base.cpp)
#list(APPEND SRC shader/vertex.cpp)
#list(APPEND SRC shader/fragment.cpp)

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS ${HUGH_LIBRARIES})
list(APPEND LIBS ${Boost_LIBRARIES})

set(LIB hugh_render_software)

cma_setup_library(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS} INCDIR hugh/render/software)
cma_setup_export(${LIB})

add_subdirectory(test EXCLUDE_FROM_ALL)
