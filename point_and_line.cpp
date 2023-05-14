#include "project.hpp"

Ric::Point Ric::intsec(Ric::Line const& r, Ric::Line const& s) {
  Ric::Point p{(s.q() - r.q()) / (r.m() - s.m()),
               (r.m() * s.q() - r.q() * s.m()) / (r.m() - s.m())};
  return p;
}

void Ric::Point::change() {
  x = -x;
  y = -y;
}

bool Ric::operator==(Ric::Point a, Ric::Point b){
    return a.x==b.x && a.y==b.y;
}

Ric::Line::Line(double m, double q) : m_{m}, q_{q} {}

Ric::Line::Line(Point a, Point b)
      : m_{(b.y - a.y) / (b.x - a.x)},
        q_{(a.y * b.x - b.y * a.x) / (b.x - a.x)} {}

Ric::Line::Line(Particle p)
      : m_{tan(p.angle())},
        q_{p.position().y - tan(p.angle()) * p.position().x} {}

double Ric::Line::m() const { return m_; }

double Ric::Line::q() const { return q_; }

double Ric::Line::angle() const { return atan(m_); }

void Ric::Line::set_last(const Ric::Point & p){
  last_=p;
}

Ric::Point Ric::Line::last() const{
  return last_;
}