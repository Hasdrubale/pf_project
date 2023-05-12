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
  Particle(Point p, double a) : position_{p}, angle_{a} {}
  Point position() const;
  double angle() const;
  void move(double const r1, double const r2, double const l);
};

class Line {
 private:
  double m_;
  double q_;

 public:
  Line(double m, double q) : m_{m}, q_{q} {}
  Line(Point a, Point b)
      : m_{(b.y - a.y) / (b.x - a.x)},
        q_{(a.y * b.x - b.y * a.x) / (b.x - a.x)} {}
  Line(Particle p)
      : m_{tan(p.angle())},
        q_{p.position().y - tan(p.angle()) * p.position().x} {}
  double m() const;
  double q() const;
  double angle() const;
};

Point intsec(Line const& r, Line const& s);
}  // namespace Ric
#endif