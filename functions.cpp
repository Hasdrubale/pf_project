#include "project.hpp"

bool Ric::operator!=(Ric::Point a, Ric::Point b) {
  return (a.x - b.x) > 0.001 || (a.y - b.y) > 0.001;
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

Ric::Line Ric::ort(const Ric::Line& r, const Ric::Point& p) {
  double new_angle{};
  if (r.angle() >= 0) {
    new_angle = -((M_PI / 2) - r.angle());
  } else {
    new_angle = (M_PI / 2) + r.angle();
  }
  Ric::Particle k{p, new_angle};
  Ric::Line l{k};
  return l;
}

void Ric::move(double const r1, double const r2, double const l,
               Ric::Particle& p) {
  Ric::Point h{0, r1};
  Ric::Point k{l, r2};
  Ric::Point i{0, 0};
  Ric::Point j{l, 0};
  Ric::Line upborder{h, k};
  h.change();
  k.change();
  Ric::Line downborder{h, k};
  Ric::Line rightborder{k, j};
  Ric::Line leftborder{i, h};
  Ric::Line go{p};
  bool exit{true};

  while (exit) {
    h = Ric::intsec(go, upborder);
    i = Ric::intsec(go, downborder);
    j = Ric::intsec(go, leftborder);
    k = Ric::intsec(go, rightborder);

    if (std::abs(j.y) < r1 && j != p.position()) {
      p.set_position(j);
      p.set_angle(-go.angle());
      go.set_new(p);
    }

    if (std::abs(k.y) < r2) {
      p.set_position(k);
      p.set_angle(go.angle());
      exit = false;
    }

    if (std::abs(i.x) > 0 && std::abs(i.x) < l && std::abs(i.y) > r2 &&
        std::abs(i.y) < r1 && i != p.position()) {
      Ric::Line s{ort(downborder, i)};
      double angle{std::abs(std::atan(go.m()) - std::atan(s.m()))};
      p.set_angle(std::atan(go.m()) - angle);
      if (std::abs(p.angle() - std::atan(s.m())) < 0.0001) {
        p.set_angle(p.angle() - angle);
      } else {
        p.set_angle(p.angle() + 3 * angle);
      }
      p.set_position(i);
      go.set_new(p);
    }

    if (std::abs(h.x) > 0 && std::abs(h.x) < l && std::abs(h.y) > r2 &&
        std::abs(h.y) < r1 && h != p.position()) {
      Ric::Line s{ort(upborder, h)};
      double angle{std::abs(std::atan(go.m()) - std::atan(s.m()))};
      p.set_angle(std::atan(go.m()) - angle);
      if (std::abs(p.angle() - std::atan(s.m())) < 0.0001) {
        p.set_angle(p.angle() - angle);
      } else {
        p.set_angle(p.angle() + 3 * angle);
      }
      p.set_position(h);
      go.set_new(p);
    }
  }
}