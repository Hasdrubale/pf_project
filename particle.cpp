#include "project.hpp"

Ric::Particle::Particle(Point p, double a) : position_{p}, angle_{a} {}

Ric::Point Ric::Particle::position() const { return position_; }

double Ric::Particle::angle() const { return angle_; }

void Ric::Particle::move(double const r1, double const r2, double const l) {
  // l'angolo di incidenza è 90 - la pendenza del bordo sotto - angolo iniziale
  // il nuovo angolo con l'asse x dopo la riflessione è 180 - 2* la pendenza del
  // bordo sotto - angolo iniziale (prima dell'urto) l'angolo va da 0 a 180
  // gradi, è con l'asse x. Per l'angolo di incidenza, se è maggiore di 90
  // gradi, utilizzare angolo - 180 (anche se negativo)
  Ric::Point h{0, r1};
  Ric::Point k{l, r2};
  Ric::Point i{};
  Ric::Point j{};
  Ric::Line upborder{h, k};
  h.change();
  k.change();
  Ric::Line downborder{h, k};
  // Ric::Line rightborder{};
  Ric::Line go{*(this)};
  go.set_last((*this).position());
  bool exit{true};
  while (exit) {
  }
}