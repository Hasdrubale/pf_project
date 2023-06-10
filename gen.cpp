#include <cassert>

#include "project.hpp"

Gen::PartG::PartG(std::default_random_engine eng, double const mean_y,
                  double const sigma_y, double const mean_ang,
                  double const sigma_ang, double const r1)
    : eng_{eng},
      mean_y_{mean_y},
      sigma_y_{sigma_y},
      mean_ang_{mean_ang},
      sigma_ang_{sigma_ang},
      r1_{r1} {}

Ric::Particle Gen::PartG::operator()() {
  std::normal_distribution<double> dist_y{mean_y_, sigma_y_};
  std::normal_distribution<double> dist_ang{mean_ang_, sigma_ang_};
  Ric::Point pos{0., dist_y(eng_)};
  Ric::Particle p{pos, dist_ang(eng_)};

  while (p.angle() <= -M_PI / 2. || p.angle() >= M_PI / 2.) {
    p.set_angle(dist_ang(eng_));
  }

  while (p.position().y >= r1_ || p.position().y <= -r1_) {
    pos.y = dist_y(eng_);
    p.set_position(pos);
  }
  return p;
}

Gen::PartM::PartM(double const r1, double const r2, double const l)
    : r1_{r1}, r2_{r2}, l_{l} {}

void Gen::PartM::operator()(Ric::Particle& p) {
  Ric::Point h{0., r1_};
  Ric::Point k{l_, r2_};
  Ric::Point i{0., 0.};
  Ric::Point j{l_, 0.};
  Ric::Line const upborder{h, k};
  h.y = -h.y;
  k.y = -k.y;
  Ric::Line const downborder{h, k};
  Ric::Line const rightborder{k, j};
  Ric::Line const leftborder{i, h};
  Ric::Line const down_perp{ort(downborder, i)};
  Ric::Line const up_perp{ort(upborder, h)};
  Ric::Line go{p};

  Ric::Particle const init{p};
  bool hit{true};

  while (true) {
    assert(std::abs(p.position().x) <= l_);
    h = Ric::intsec(go, upborder);
    i = Ric::intsec(go, downborder);
    j = Ric::intsec(go, leftborder);
    k = Ric::intsec(go, rightborder);

    if (std::abs(j.y) <= r1_ && j != p.position()) {
      p.set_position(j);
      p.set_angle(-go.angle());
      go.set_new(p);
      continue;
    }

    if (std::abs(k.y) <= r2_) {
      p.set_position(k);
      p.set_angle(go.angle());
      break;
    }

    if (std::abs(i.x) >= 0 && std::abs(i.x) <= l_ && std::abs(i.y) >= r2_ &&
        std::abs(i.y) <= r1_ && i != p.position()) {
      double const angle = Ric::find_angle(down_perp, go);
      p.rotate_forward(angle);
      if (std::abs(p.angle() - std::atan(down_perp.m())) < 0.0001) {
        p.rotate_forward(angle);
      } else {
        p.rotate_backward(angle);
        p.rotate_backward(angle);
        p.rotate_backward(angle);
      }
      p.set_position(i);
      go.set_new(p);
      continue;
    }

    if (std::abs(h.x) >= 0 && std::abs(h.x) <= l_ && std::abs(h.y) >= r2_ &&
        std::abs(h.y) <= r1_ && h != p.position()) {
      double const angle = Ric::find_angle(up_perp, go);
      p.rotate_forward(angle);
      if (std::abs(p.angle() - std::atan(up_perp.m())) < 0.0001) {
        p.rotate_forward(angle);
      } else {
        p.rotate_backward(angle);
        p.rotate_backward(angle);
        p.rotate_backward(angle);
      }
      p.set_position(h);
      go.set_new(p);
      continue;
    }

    if (hit) {
      p.set_position(init.position());
      p.set_angle(-init.angle());
      go.set_new(p);
      hit = false;
    } else {
      break;
    }
  }
}