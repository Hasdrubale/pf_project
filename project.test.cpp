#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "project.hpp"

#include "doctest.h"

TEST_CASE("Testing lines") {
  SUBCASE("Line constructors") {
    Ric::Point a{1., 2.};
    Ric::Point b{3., -5.};
    const Ric::Line r{a, b};
    CHECK(r.a() == doctest::Approx(-7.));
    CHECK(r.b() == doctest::Approx(-2.));
    CHECK(r.c() == doctest::Approx(11.));
    CHECK(r.angle() == doctest::Approx(-1.2925));
    const Ric::Particle p{a, M_PI / 4};
    const Ric::Line s{p};
    CHECK(s.a() == doctest::Approx(sqrt(2.) / 2));
    CHECK(s.b() == doctest::Approx(-sqrt(2.) / 2));
    CHECK(s.c() == doctest::Approx(sqrt(2.) / 2));
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

TEST_CASE("Testing perpendicular line function") {
  Ric::Point p{5., 3.};
  Ric::Point q{1., -2.};
  Ric::Line r{p, q};
  Ric::Line s{ort(r, p)};
  CHECK(s.m() == doctest::Approx(-0.8));
  CHECK(s.q() == doctest::Approx(7.));
}

TEST_CASE("Testing the motion") {
  SUBCASE("Test 1") {
    double l{10.};
    double r1{5.};
    double r2{3.};
    Ric::Point p0{0., 4.};
    Ric::Particle p{p0, M_PI / 4};
    move(r1, r2, l, p);
    CHECK(p.position().y == doctest::Approx(-1.8798));
    CHECK(p.angle() == doctest::Approx(-22.8596 * 2 * M_PI / 360));
  }
  SUBCASE("Test 2") {
    double l{6.};
    double r1{5.};
    double r2{3.};
    Ric::Point p0{0., 2.};
    Ric::Particle p{p0, -M_PI / 6};
    move(r1, r2, l, p);
    CHECK(p.position().y == doctest::Approx(-1.4641));
    CHECK(p.angle() == doctest::Approx(-M_PI / 6));
  }
  SUBCASE("Test 3") {
    double l{14.};
    double r1{7.};
    double r2{4.};
    Ric::Point p0{0., -1.};
    Ric::Particle p{p0, M_PI / 3};
    move(r1, r2, l, p);
    CHECK(p.position().y == doctest::Approx(3.4707));
    CHECK(p.angle() == doctest::Approx(M_PI / 3));
  }
}