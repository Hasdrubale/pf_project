#include <algorithm>
#include <iostream>
#include <string>

#include "project.hpp"

Stats::Sample::Sample(std::vector<Ric::Particle> particles)
    : particles_{particles} {}

const Stats::Statistics Stats::Sample::statistics_y() const {
  std::vector<double> ys;
  ys.resize(particles_.size());
  std::transform(particles_.begin(), particles_.end(), ys.begin(),
                 [](const Ric::Particle p) { return p.position().y; });
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