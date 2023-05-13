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
  SUBCASE("Test 1") {
    double l{10.};
    double r1{5.};
    double r2{3.};
    Ric::Point p0{0., 4.};
    Ric::Particle p{p0, M_PI / 4};
    p.move(r1, r2, l);
    CHECK(p.position().y==doctest::Approx(-1.8798));
    CHECK(p.angle()==doctest::Approx(-22.8596*2*M_PI/360));
  }
    SUBCASE("Test 2") {
    double l{6.};
    double r1{5.};
    double r2{3.};
    Ric::Point p0{0., 2.};
    Ric::Particle p{p0, -M_PI / 6};
    p.move(r1, r2, l);
    CHECK(p.position().y==doctest::Approx(-1.4641));
    CHECK(p.angle()==doctest::Approx(-M_PI/6));
  }
    SUBCASE("Test 3") {
    double l{14.};
    double r1{7.};
    double r2{4.};
    Ric::Point p0{0., -1.};
    Ric::Particle p{p0, M_PI / 3};
    p.move(r1, r2, l);
    CHECK(p.position().y==doctest::Approx(3.4707));
    CHECK(p.angle()==doctest::Approx(M_PI/3));
  }
}