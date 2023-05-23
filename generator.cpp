#include "project.hpp"

Gen::PartG::PartG(std::default_random_engine eng) : eng_{eng} {};

Ric::Particle Gen::PartG::operator()(double const mean_y, double const sigma_y,
                                     double const mean_ang,
                                     double const sigma_ang, double const r1) {
  std::normal_distribution<double> dist_y{mean_y, sigma_y};
  std::normal_distribution<double> dist_ang{mean_ang, sigma_ang};
  Ric::Point pos{0., dist_y(eng_)};
  Ric::Particle p{pos, dist_ang(eng_)};

  while (p.angle() <= -M_PI / 2 || p.angle() >= M_PI / 2) {
    p.set_angle(dist_ang(eng_));
  }

  while (p.position().y >= r1 || p.position().y <= -r1) {
    pos.y = dist_y(eng_);
    p.set_position(pos);
  }
  return p;
}