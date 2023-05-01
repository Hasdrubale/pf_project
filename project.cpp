#include "project.hpp"
Ric::Point Ric::intsec(Ric::Line const& r, Ric::Line const& s) {
  Ric::Point p{(s.q() - r.q()) / (r.m() - s.m()),
               (r.m() * s.q() - r.q() * s.m()) / (r.m() - s.m())};
  return p;
}
double Ric::Line::m() const { return m_; }
double Ric::Line::q() const { return q_; }