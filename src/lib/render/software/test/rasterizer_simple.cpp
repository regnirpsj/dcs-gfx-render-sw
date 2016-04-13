// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/rasterizer/simple.cpp                                 */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <array>          // std::array<>
#include <glm/gtx/io.hpp> // glm::operator<<

// includes, project

#include <hugh/render/software/rasterizer/simple.hpp>
#include <hugh/support/io_utils.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_render_software_rasterizer_simple_ctor)
{
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;
  
  {
    rasterizer::simple const rs;

    BOOST_CHECK(viewport() == *rs.viewport);
  }

  {
    viewport const           vp(0, 0, 10, 10);
    rasterizer::simple const rs(vp);
  
    BOOST_CHECK(vp == *rs.viewport);
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_rasterizer_simple_process_line)
{
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;

  viewport const  v(0, 0,  4,  3); // adj:  0
  //viewport const  v(0, 0,  8,  6); // adj: -1
  //viewport const  v(0, 0, 16, 12); // adj: -3
  //viewport const  v(0, 0, 24, 18); // adj: -5
  //viewport const  v(0, 0, 40, 30); // adj: -9
  // w*w+h*h needs to be a square number for 'd' to make sense
  unsigned const  d(std::sqrt((v. width * v. width) + (v.height * v.height)));
  glm::vec3 const o(      0,        0, 0);
  glm::vec3 const x(v.width,        0, 0);
  glm::vec3 const y(      0, v.height, 0);
  glm::vec3 const z(      0,        0, 1);
  
  std::array<std::pair<line const, unsigned const>, 22> const lines = {
    {
      { line(o,   x), v. width+1 }, { line(  x, o), v. width+1 },
      { line(o,  -x),          1 }, { line( -x, o),          1 },
      { line(x,  -x), v. width+1 }, { line( -x, x), v. width+1 },
      { line(o,   y), v.height+1 }, { line(  y, o), v.height+1 },
      { line(o,  -y),          1 }, { line( -y, o),          1 },
      { line(y,  -y), v.height+1 }, { line( -y, y), v.height+1 },
      { line(o,   z),          1 }, { line(  z, o),          1 },
      { line(o,  -z),          1 }, { line( -z, o),          1 },
      { line(z,  -z),          1 }, { line( -z, z),          1 },
      { line(o, x+y),          d }, { line(x+y, o),          d },
      { line(y,   x),          d }, { line(  x, y),          d },
    }
  };
  
  rasterizer::simple const rs(v);

  for (auto const& lp : lines) {
    using fragment_list = rasterizer::simple::fragment_list_type;
    
    fragment_list const fl(rs.process(lp.first));
    
    BOOST_CHECK(lp.second == fl.size());

    {
      std::ostringstream ostr;
      
      using hugh::support::ostream::operator<<;

      ostr << lp.second << "=?=" << fl.size() << ':'
           << glm::io::width(2) << glm::io::precision(0) << fl;
      
      BOOST_TEST_MESSAGE(ostr.str());
    }
  }

  BOOST_TEST_MESSAGE('\n');
}

template <typename T>
glm::tvec3<T>
two(glm::tvec3<T> const& a)
{
  return a * T(2);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_rasterizer_simple_process_triangle)
{
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;

  //viewport const  v(0, 0,  4,  3); // adj: +1, -2
  viewport const  v(0, 0,  8,  6); // adj: +2, -3
  //viewport const  v(0, 0, 16, 12); // adj: +3
  //viewport const  v(0, 0, 24, 18); // adj: +4
  //viewport const  v(0, 0, 40, 30); // adj: +6
  unsigned const  a((((v.width+1) * (v.height+1)) / 2) + 2);
  glm::vec3 const o(      0,        0, 0);
  glm::vec3 const x(v.width,        0, 0);
  glm::vec3 const y(      0, v.height, 0);
  glm::vec3 const z(      0,        0, 1);
  
  std::array<std::pair<triangle const, unsigned const>, 18> const triangles = {
    {
      { triangle(o, x, y), a }, { triangle(o, y, x), 0 },
      { triangle(x, y, o), a }, { triangle(y, x, o), 0 },
      { triangle(y, o, x), a }, { triangle(x, o, y), 0 },
      
      { triangle(x, x+y, y), a }, { triangle(x, y, x+y), 0 },
      { triangle(x+y, y, x), a }, { triangle(y, x+y, x), 0 },
      { triangle(y, x, x+y), a }, { triangle(x+y, x, y), 0 },

      { triangle(o, two(x), two(y)), (2.f*a)-3 }, { triangle(o, 2.f*y, 2.f*x), 0 },
      { triangle(two(x), two(y), o), (2.f*a)-3 }, { triangle(2.f*y, 2.f*x, o), 0 },
      { triangle(two(y), o, two(x)), (2.f*a)-3 }, { triangle(2.f*x, o, 2.f*y), 0 },
    }
  };
  
  rasterizer::simple const rs(v);

  for (auto const& tp : triangles) {
    using fragment_list = rasterizer::simple::fragment_list_type;
    
    fragment_list const fl(rs.process(tp.first));
    
    BOOST_CHECK(tp.second == fl.size());

    {
      std::ostringstream ostr;
      
      using hugh::support::ostream::operator<<;

      ostr << tp.second << "=?=" << fl.size() << ':'
           << glm::io::width(2) << glm::io::precision(0) << fl;
      
      BOOST_TEST_MESSAGE(ostr.str());
    }
  }

  BOOST_TEST_MESSAGE('\n');
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_rasterizer_simple_print_on)
{
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;
  
  rasterizer::simple const rs(viewport(0, 0, 10, 10));
  std::ostringstream       ostr;

  ostr << rs;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
