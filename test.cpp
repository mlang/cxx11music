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

BOOST_AUTO_TEST_CASE(udliterals) {
  using namespace musical;
  BOOST_REQUIRE_EQUAL(4*16_th, rational(1, 4));
}
