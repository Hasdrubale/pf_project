#include <cassert>
#include <iostream>

#include "project.hpp"

int main() {

  double r1{};
  double r2{};
  double l{};

  std::cout << "Inserire r1: ";
  std::cin >> r1;
  std::cout << "Inserire r2: ";
  std::cin >> r2;
  std::cout << "Inserire l: ";
  std::cin >> l;

  bool exit = true;
  while (exit) {
    char command{};
    std::cout << "Comando: ";
    std::cin >> command;
    assert(command == 's' || command == 'm' || command == 'q');
    if (command == 's') {
      double y{};
      double ang{};
      std::cout << "Inserire y0: ";
      std::cin >> y;
      assert(abs(y) < r1);
      std::cout << "Inserire angolo di partenza: ";
      std::cin >> ang;
      assert(ang < M_PI && ang > 0);
      Ric::Point pos{0, y};
      Ric::Particle p{pos, ang};
      p.move(r1, r2, l);
      std::cout << "Y finale: " << p.position().y << "\n"
                << "Angolo: " << p.angle() << "\n";
    }
    if (command == 'm') {
      int n{};
      std::cout << "Inserire numero particelle: ";
      std::cin >> n;
      // completare
    }
    if (command == 'q') {
      exit = false;
    }
  }
}
