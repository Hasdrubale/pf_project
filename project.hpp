#ifndef PROJECT_HPP
#define PROJECT_HPP
namespace Ric {
struct Point {
  double x;
  double y;
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
  double m() const;
  double q() const;
};
}  // namespace Ric
#endif