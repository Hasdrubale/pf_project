#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <cmath>

namespace Ric {

struct Point {
  double x;
  double y;
  void change();
};

class Particle {
 private:
  Point position_;
  double angle_;

 public:
  Particle(Point p, double a);
  Point position() const;
  double angle() const;
  void move(double const r1, double const r2, double const l);
};

class Line {
 private:
  double m_;
  double q_;

 public:
  Line(double m, double q);
  Line(Point a, Point b);
  Line(Particle p);
  double m() const;
  double q() const;
  double angle() const;
};

Point intsec(Line const& r, Line const& s);
}  // namespace Ric
#endif