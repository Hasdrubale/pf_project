#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "project.hpp"

#include "doctest.h"

TEST_CASE("Testing lines") {
  SUBCASE("Line constructors") {
    Ric::Point a{1., 2.};
    Ric::Point b{3., -5.};
    const Ric::Line r{a, b};
    CHECK(r.m() == doctest::Approx(-3.5));
    CHECK(r.q() == doctest::Approx(5.5));
    CHECK(r.angle() == doctest::Approx(-1.2925));
    const Ric::Particle p{a, M_PI / 4};
    const Ric::Line s{p};
    CHECK(s.m() == doctest::Approx(1.));
    CHECK(s.q() == doctest::Approx(1.));
    CHECK(s.angle() == doctest::Approx(M_PI / 4));
  }
  SUBCASE("Lines intersection") {
    Ric::Line r{3., 2.};
    Ric::Line s{-2., 1.};
    Ric::Point p = Ric::intsec(r, s);
    CHECK(p.x == doctest::Approx(-0.2));
    CHECK(p.y == doctest::Approx(1.4));
  }
}

TEST_CASE("Testing the motion") {
  SUBCASE("Test 1") {}
}