#include "project.hpp"

bool Ric::operator!=(Ric::Point a, Ric::Point b) {
  return (a.x - b.x) > 0.001 || (a.y - b.y) > 0.001;
}

Ric::Point Ric::intsec(Ric::Line const& r, Ric::Line const& s) {
  double det{r.a() * s.b() - r.b() * s.a()};
  if (std::abs(det) < 0.00000001) {
    // throw, o metti un valore molto alto per il metodo move
  }
  Ric::Point p{(r.b() * s.c() - s.b() * r.c()) / (det),
               (s.a() * r.c() - r.a() * s.c()) / (det)};
  return p;
}

Ric::Line Ric::ort(const Ric::Line& r, const Ric::Point& p) {}

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

    if (std::abs(j.y) < r1 && j !=) {
    }
  }
}