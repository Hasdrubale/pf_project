#include <cassert>
#include <cmath>

#include "project.hpp"

Ric::Line::Line(double m, double q) : a_{m}, b_{-1.}, c_{q} {}

Ric::Line::Line(Point a, Point b)
    : a_{(b.y - a.y)}, b_{(a.x - b.x)}, c_{a.y * b.x - b.y * a.x} {}

Ric::Line::Line(Particle p)
    : a_{std::sin(p.angle())},
      b_{-std::cos(p.angle())},
      c_{std::cos(p.angle()) * p.position().y -
         std::sin(p.angle()) * p.position().x} {}

double Ric::Line::a() const { return a_; }

double Ric::Line::b() const { return b_; }

double Ric::Line::c() const { return c_; }

double Ric::Line::angle() const {
  if (b_ == 0.) {
    return M_PI / 2;
  } else {
    return std::atan(-a_ / b_);
  }
}

double Ric::Line::m() const { return -(a_ / b_); }

double Ric::Line::q() const { return -(c_ / b_); }

void Ric::Line::set_new(Particle const p) {
  Ric::Line l{p};
  a_ = l.a();
  b_ = l.b();
  c_ = l.c();
}

Ric::Particle::Particle(Point p, double a) : position_{p}, angle_{a} {}

Ric::Point Ric::Particle::position() const { return position_; }

double Ric::Particle::angle() const { return angle_; }

void Ric::Particle::set_position(Ric::Point const& p) { position_ = p; }

void Ric::Particle::set_angle(double const r) { angle_ = r; }

void Ric::Particle::rotate_backward(double const angle) {
  assert(angle <= M_PI / 2 && angle >= 0);
  double a{angle_};
  a -= angle;
  if (a < -M_PI / 2) {
    a += M_PI;
  }
  angle_ = a;
  assert(std::abs(angle_) <= M_PI / 2);
}

void Ric::Particle::rotate_forward(double const angle) {
  assert(angle <= M_PI / 2 && angle >= 0);
  double a{angle_};
  a += angle;
  if (a > M_PI / 2) {
    a -= M_PI;
  }
  angle_ = a;
  assert(std::abs(angle_) <= M_PI / 2);
}
