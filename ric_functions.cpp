#include <cassert>
#include <cmath>
#include <iostream>

#include "project.hpp"

bool Ric::operator!=(Ric::Point a, Ric::Point b) {
  return std::abs((a.x - b.x)) > 0.001 || std::abs((a.y - b.y)) > 0.001;
}

Ric::Point Ric::intsec(Ric::Line const& r, Ric::Line const& s) {
  double det{r.a() * s.b() - r.b() * s.a()};
  if (std::abs(det) < 0.00000001) {
    Ric::Point p{1000000., 1000000.};
    return p;  // ritorna un valore altissimo, in modo che la funzione move non
               // lo prenda in considerazione
  }
  Ric::Point p{(r.b() * s.c() - s.b() * r.c()) / (det),
               (s.a() * r.c() - r.a() * s.c()) / (det)};
  return p;
}

Ric::Line const Ric::ort(const Ric::Line& r, const Ric::Point& p) {
  double new_angle{};
  if (r.angle() >= 0) {
    new_angle = -((M_PI / 2) - r.angle());
  } else {
    new_angle = (M_PI / 2) + r.angle();
  }
  Ric::Particle const k{p, new_angle};
  Ric::Line const l{k};
  return l;
}

double Ric::find_angle(Ric::Line const& r, Ric::Line const& s) {
  double r_ang{};
  double s_ang{};
  if (r.m() < 0) {
    r_ang = M_PI + std::atan(r.m());
  } else {
    r_ang = std::atan(r.m());
  }
  if (s.m() < 0) {
    s_ang = M_PI + std::atan(s.m());
  } else {
    s_ang = std::atan(s.m());
  }
  assert(r_ang >= 0 && r_ang <= M_PI);
  assert(s_ang >= 0 && s_ang <= M_PI);
  double ang{std::abs(r_ang - s_ang)};
  assert(ang >= 0 && ang <= M_PI);
  if (ang > M_PI / 2) {
    ang = M_PI - ang;
  }
  return ang;
}