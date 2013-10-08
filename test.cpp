#include "cxx11music.hpp"
#define BOOST_TEST_MODULE cxx11musictest
#ifdef BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#else
#include <boost/test/included/unit_test.hpp>
#endif

BOOST_AUTO_TEST_CASE(append) {
  using namespace musical;
  stream s;
  note n;
  s.append(n);
  BOOST_REQUIRE_EQUAL(n.offset(s), rational{});
}

