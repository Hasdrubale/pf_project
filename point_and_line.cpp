#include "project.hpp"

Ric::Point Ric::intsec(Ric::Line const& r, Ric::Line const& s) {
  double det{r.a() * s.b() - r.b() * s.a()};
  if(std::abs(det)<0.00000001){
    //throw, o metti un valore molto alto per il metodo move
  }
  Ric::Point p{(r.b() * s.c() - s.b() * r.c()) / (det),
               (s.a() * r.c() - r.a() * s.c()) / (det)};
  return p;
}

void Ric::Point::change() {
  x = -x;
  y = -y;
}

bool Ric::operator==(Ric::Point a, Ric::Point b) {
  return a.x == b.x && a.y == b.y;
}

Ric::Line::Line(double m, double q) : a_{m}, b_{-1.}, c_{q} {}

Ric::Line::Line(Point a, Point b)
    : a_{(b.y - a.y)}, b_{(a.x - b.x)}, c_{a.y * b.x - b.y * a.x} {}

Ric::Line::Line(Particle p)
    : a_{std::sin(p.angle())},
      b_{-std::cos(p.angle())},
      c_{std::cos(p.angle()) * p.position().y - std::sin(p.angle()) * p.position().x} {}

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

void Ric::Line::set_last(const Ric::Point& p) { last_ = p; }

Ric::Point Ric::Line::last() const { return last_; }