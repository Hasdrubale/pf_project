#include <algorithm>

#include "project.hpp"

Stats::Sample::Sample(std::vector<Ric::Particle> particles)
    : particles_{particles} {}

std::vector<Ric::Particle> Stats::Sample::vec() {
  return particles_;
}

Stats::Statistics Stats::Sample::statistics_y() {
  std::vector<double> ys;
  ys.reserve(particles_.size());
  std::transform(particles_.begin(), particles_.end(), ys.begin(),
                 [](Ric::Particle p) { return p.position().y; });
  double mean{std::accumulate(ys.begin(), ys.end(), 0.) / particles_.size()};
  double sigma{sqrt((std::accumulate(ys.begin(), ys.end(), 0.,
                                     [=](double acc, double i) {
                                       return acc + (i - mean) * (i - mean);
                                     }) /
                     (particles_.size() - 1)))};
  double simm{(std::accumulate(ys.begin(), ys.end(), 0.,
                               [=](double acc, double i) {
                                 return acc + ((i - mean) / sigma) *
                                                  ((i - mean) / sigma) *
                                                  ((i - mean) / sigma);
                               }) /
               (particles_.size()))};
  double app{(std::accumulate(ys.begin(), ys.end(), 0.,
                              [=](double acc, double i) {
                                return acc + ((i - mean) / sigma) *
                                                 ((i - mean) / sigma) *
                                                 ((i - mean) / sigma) *
                                                 ((i - mean) / sigma);
                              }) /
              (particles_.size()))};
  Statistics statistics{mean, sigma, simm, app};
  return statistics;
}

Stats::Statistics Stats::Sample::statistics_ang() {}