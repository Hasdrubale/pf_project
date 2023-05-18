#ifndef PROJECT_HPP
#define PROJECT_HPP

namespace Ric {

struct Point {
  double x{0.};
  double y{0.};
};

class Particle {
 private:
  Point position_;
  double angle_;

 public:
  Particle(Point p, double a);
  Point position() const;
  double angle() const;
  void set_position(Point const);
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
  Point last_{};

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
  void set_new(Particle const);
};

bool operator!=(Point a, Point b);

Point intsec(Line const& r, Line const& s);

Line const ort(Line const&, Point const&);

void move(double const, double const, double const, Ric::Particle&);

double find_angle(Line const&, Line const&);
}  // namespace Ric

#endif