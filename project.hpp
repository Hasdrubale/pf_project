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
};

bool operator!=(Point a, Point b);

Point intsec(Line const& r, Line const& s);

Line ort(Line const&, Point const&);

void move(double const, double const, double const, Ric::Particle&);

}  // namespace Ric

#endif