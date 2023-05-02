#include "project.hpp"
Ric::Point Ric::intsec(Ric::Line const& r, Ric::Line const& s) {
  Ric::Point p{(s.q() - r.q()) / (r.m() - s.m()),
               (r.m() * s.q() - r.q() * s.m()) / (r.m() - s.m())};
  return p;
}
double Ric::Line::m() const { return m_; }
double Ric::Line::q() const { return q_; }
Ric::Point Ric::Particle::position() const { return position_; }
double Ric::Particle::angle() const { return angle_; }
void Ric::Particle::move(double const r1, double const r2, double const l) {
  // l'angolo di incidenza è 90 - la pendenza del bordo sotto - angolo iniziale
  // il nuovo angolo con l'asse x dopo la riflessione è 180 - 2* la pendenza del
  // bordo sotto - angolo iniziale (prima dell'urto) l'angolo va da 0 a 180
  // gradi, è con l'asse x. Per l'angolo di incidenza, se è maggiore di 90
  // gradi, utilizzare angolo - 180 (anche se negativo)
}