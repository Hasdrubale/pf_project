#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <fstream>
#include <random>

namespace Ric {

struct Point {
  double x{0.};
  double y{0.};
};

class Particle {
 private:
  Point position_{};
  double angle_{};

 public:
  Particle(Point p, double a);
  Point position() const;
  double angle() const;
  void set_position(Point const&);
  void set_angle(double const);
  void rotate_forward(double const);
  void rotate_backward(double const);
};

class Line {
 private:
  // ax+by+c=0
  double a_;
  double b_;
  double c_;

 public:
  Line(double m, double q);
  Line(Point a, Point b);
  Line(Particle p);
  double a() const;
  double b() const;
  double c() const;
  double m() const;
  double q() const;
  double angle() const;
  void set_new(Particle const);  // riguarda assignment
};

bool operator!=(Point a, Point b);

Point intsec(Line const& r, Line const& s);  // controlla constness

Line const ort(Line const&, Point const&);

double find_angle(Line const&, Line const&);

}  // namespace Ric

namespace Gen {

class PartG {
  std::default_random_engine eng_;
  double const mean_y_;
  double const sigma_y_;
  double const mean_ang_;
  double const sigma_ang_;
  double const r1_;

 public:
  PartG(std::default_random_engine eng, double const mean_y,
        double const sigma_y, double const mean_ang, double const sigma_ang,
        double const r1);
  Ric::Particle operator()();
};

class PartM {
  double const r1_;
  double const r2_;
  double const l_;

 public:
  PartM(double const r1, double const r2, double const l);
  void operator()(Ric::Particle& p);
};
}  // namespace Gen

namespace Stats {

struct Statistics {
  double mean{};
  double sigma{};
  double simm{};
  double app{};
};

class Sample {
 private:
  std::vector<Ric::Particle> particles_{};

 public:
  Sample(std::vector<Ric::Particle> particles);
  const Statistics statistics_y() const;
  const Statistics statistics_ang() const;
};

}  // namespace Stats
#endif