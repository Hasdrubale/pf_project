#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <cmath>

namespace Ric {

struct Point {
  double x{0.};
  double y{0.};
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
  // ax+by+c=0
  double a_;
  double b_;
  double c_;
  Point last_{};

 public:
  Line(double m, double q);
  Line(Point a, Point b);
  Line(Particle p);
  double a() const;
  double b() const;
  double c() const;
  double angle() const;
  void set_last(Point const&);
  Point last() const;
};

bool operator==(Point a, Point b);

Point intsec(Line const& r, Line const& s);
}  // namespace Ric

#endif