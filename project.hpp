#ifndef PROJECT_HPP
#define PROJECT_HPP
#include <cmath>
namespace Ric {
struct Point {
  double x;
  double y;
};
struct Particle {
  Point position;
  double angle;
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
      : m_{tan(p.angle)}, q_{p.position.y - tan(p.angle) * p.position.x} {}
  double m() const;
  double q() const;
};
Point intsec(Line const& r, Line const& s);
}  // namespace Ric
#endif