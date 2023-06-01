#include <algorithm>

#include "project.hpp"

Stats::Sample::Sample(std::vector<Ric::Particle> particles)
    : particles_{particles} {}

std::vector<Ric::Particle> Stats::Sample::vec() { return particles_; }

const Stats::Statistics Stats::Sample::statistics_y() const{
  std::vector<double> ys;
  ys.resize(particles_.size());
  std::transform(particles_.begin(), particles_.end(), ys.begin(),
                 [](Ric::Particle p) { return p.position().y; });
  double mean{std::accumulate(ys.begin(), ys.end(), 0.) / ys.size()};
  double sigma{sqrt((std::accumulate(ys.begin(), ys.end(), 0.,
                                     [=](double acc, double i) {
                                       return acc + (i - mean) * (i - mean);
                                     }) /
                     (ys.size() - 1)))};
  double simm{(std::accumulate(ys.begin(), ys.end(), 0.,
                               [=](double acc, double i) {
                                 return acc + ((i - mean) / sigma) *
                                                  ((i - mean) / sigma) *
                                                  ((i - mean) / sigma);
                               }) /
               (ys.size()))};
  double app{(std::accumulate(ys.begin(), ys.end(), 0.,
                              [=](double acc, double i) {
                                return acc + ((i - mean) / sigma) *
                                                 ((i - mean) / sigma) *
                                                 ((i - mean) / sigma) *
                                                 ((i - mean) / sigma);
                              }) /
              (ys.size()))};
  Statistics statistics{mean, sigma, simm, app};
  return statistics;
}

const Stats::Statistics Stats::Sample::statistics_ang() const {
  std::vector<double> ys;
  ys.resize(particles_.size());
  std::transform(particles_.begin(), particles_.end(), ys.begin(),
                 [](Ric::Particle p) { return p.angle(); });
  double mean{std::accumulate(ys.begin(), ys.end(), 0.) / ys.size()};
  double sigma{sqrt((std::accumulate(ys.begin(), ys.end(), 0.,
                                     [=](double acc, double i) {
                                       return acc + (i - mean) * (i - mean);
                                     }) /
                     (ys.size() - 1)))};
  double simm{(std::accumulate(ys.begin(), ys.end(), 0.,
                               [=](double acc, double i) {
                                 return acc + ((i - mean) / sigma) *
                                                  ((i - mean) / sigma) *
                                                  ((i - mean) / sigma);
                               }) /
               (ys.size()))};
  double app{(std::accumulate(ys.begin(), ys.end(), 0.,
                              [=](double acc, double i) {
                                return acc + ((i - mean) / sigma) *
                                                 ((i - mean) / sigma) *
                                                 ((i - mean) / sigma) *
                                                 ((i - mean) / sigma);
                              }) /
              (ys.size()))};
  Statistics statistics{mean, sigma, simm, app};
  return statistics;
}

void Stats::Sample::read(std::string s) {
  std::ifstream file{s};
  while (true) {
    double x;
    double y;
    double ang;
    file >> x;
    file >> y;
    file >> ang;
    if (file) {
      Ric::Point p{x, y};
      Ric::Particle par{p, ang};
      particles_.push_back(par);
    } else {
      break;
    }
  }
}