#include "project.hpp"

Gen::PartG::PartG(std::default_random_engine eng, double const mean_y,
                  double const sigma_y, double const mean_ang,
                  double const sigma_ang, double const r1)
    : eng_{eng}, mean_y_{mean_y}, sigma_y_{sigma_y}, mean_ang_{mean_ang}, sigma_ang_{sigma_ang}, r1_{r1}{};

Ric::Particle Gen::PartG::operator()() {
  std::normal_distribution<double> dist_y{mean_y_, sigma_y_};
  std::normal_distribution<double> dist_ang{mean_ang_, sigma_ang_};
  Ric::Point pos{0., dist_y(eng_)};
  Ric::Particle p{pos, dist_ang(eng_)};

  while (p.angle() <= -M_PI / 2 || p.angle() >= M_PI / 2) {
    p.set_angle(dist_ang(eng_));
  }

  while (p.position().y >= r1_ || p.position().y <= -r1_) {
    pos.y = dist_y(eng_);
    p.set_position(pos);
  }
  return p;
}