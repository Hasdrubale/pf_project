#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "project.hpp"

#include "doctest.h"

TEST_CASE("Testing line constructor") {
  Ric::Point a{1., 2.};
  Ric::Point b{3., -5.};
  Ric::Line r{a, b};
  CHECK(r.m() == doctest::Approx(-3.5));
  CHECK(r.q() == doctest::Approx(5.5));
}