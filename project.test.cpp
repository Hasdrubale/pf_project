#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "project.hpp"

#include "doctest.h"

TEST_CASE("Testing lines") {
  SUBCASE("Line constructors") {
    Ric::Point const a{1., 2.};
    Ric::Point const b{3., -5.};
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
    Ric::Line const r{3., 2.};
    Ric::Line const s{-2., 1.};
    Ric::Point const p = Ric::intsec(r, s);
    CHECK(p.x == doctest::Approx(-0.2));
    CHECK(p.y == doctest::Approx(1.4));
  }
}

TEST_CASE("Testing perpendicular line function") {
  Ric::Point const p{5., 3.};
  Ric::Point const q{1., -2.};
  Ric::Line const r{p, q};
  Ric::Line const s{ort(r, p)};
  CHECK(s.m() == doctest::Approx(-0.8));
  CHECK(s.q() == doctest::Approx(7.));
}

TEST_CASE("Testing the motion") {
  SUBCASE("Test 1") {
    double const l{10.};
    double const r1{5.};
    double const r2{3.};
    Ric::Point p0{0., 4.};
    Ric::Particle p{p0, M_PI / 4};
    Gen::PartM move{r1, r2, l};
    move(p);
    CHECK(p.position().y == doctest::Approx(-1.8798));
    CHECK(p.angle() == doctest::Approx(-67.14040516 * 2 * M_PI / 360));
  }
  SUBCASE("Test 2") {
    double const l{6.};
    double const r1{5.};
    double const r2{3.};
    Ric::Point p0{0., 2.};
    Ric::Particle p{p0, -M_PI / 6};
    Gen::PartM move{r1, r2, l};
    move(p);
    CHECK(p.position().y == doctest::Approx(-1.4641));
    CHECK(p.angle() == doctest::Approx(-M_PI / 6));
  }
  SUBCASE("Test 3") {
    double const l{14.};
    double const r1{7.};
    double const r2{4.};
    Ric::Point p0{0., -1.};
    Ric::Particle p{p0, M_PI / 3};
    Gen::PartM move{r1, r2, l};
    move(p);
    CHECK(p.position().y == doctest::Approx(3.4707));
    CHECK(p.angle() == doctest::Approx(M_PI / 3));
  }
}

TEST_CASE("Testing statistics") {
  std::vector<Ric::Particle> particles{};
  Ric::Point const p1{0., 1.6};
  Ric::Point const p2{0., 2.7};
  Ric::Point const p3{0., 3.5};
  Ric::Particle const par1{p1, -0.7};
  Ric::Particle const par2{p2, 0.5};
  Ric::Particle const par3{p3, 1.2};
  particles.push_back(par1);
  particles.push_back(par2);
  particles.push_back(par3);

  Stats::Sample c{particles};
  Stats::Statistics y{c.statistics_y()};
  // Stats::Statistics ang{c.statistics_ang()};

  CHECK(y.mean == doctest::Approx(2.6));
  CHECK(y.sigma == doctest::Approx(0.953939));
  CHECK(y.simm == doctest::Approx(-0.103676));
  CHECK(y.app == doctest::Approx(0.66666));
  CHECK(c.vec().size() == 3);
  // CHECK(ang.mean == doctest::Approx(0.333333));
  // CHECK(ang.sigma == doctest::Approx(0.960902));
  // CHECK(ang.simm == doctest::Approx(-0.16823));
  // CHECK(ang.app == doctest::Approx(0.66666));
}