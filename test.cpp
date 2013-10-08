#include "cxx11music.hpp"
#define BOOST_TEST_MODULE cxx11musictest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(append) {
  using namespace musical;
  stream s;
  note n;
  s.append(n);
  BOOST_REQUIRE_EQUAL(n.offset(s), rational{});
}

