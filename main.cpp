#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>

#include "project.hpp"

int main() {
  double r1{};
  double r2{};

  while (true) {
    char command{};
    std::cout << "Comando: ";
    std::cin >> command;
    assert(command == 'm' || command == 'a' || command == 'q');

    if (command == 'm') {
      double l{};
      double y{};
      double ang{};
      std::cout << "Inserire r1: ";
      std::cin >> r1;
      std::cout << "Inserire r2: ";
      std::cin >> r2;
      assert(r2 > 0 && r2 < r1);
      std::cout << "Inserire l: ";
      std::cin >> l;
      std::cout << "Inserire y0: ";
      std::cin >> y;
      assert(abs(y) < r1);
      std::cout << "Inserire angolo di partenza (in gradi): ";
      std::cin >> ang;
      ang = (ang / 360.) * 2 * M_PI;
      assert(ang < M_PI / 2 && ang > -M_PI / 2);
      Ric::Point pos{0, y};
      Ric::Particle p{pos, ang};
      Gen::PartM move{r1, r2, l};
      p = move(p);
      std::cout << "Y finale: " << p.position().y << "\n"
                << "Angolo (radianti):" << p.angle() << "\n"
                << "Angolo (gradi): " << ((p.angle() / (2 * M_PI)) * 360)
                << "\n";
      continue;
    }

    if (command == 'a') {
      int n{};
      double l_min{};
      double l_max{};
      double step{};
      double mean_y{};
      double sigma_y{};
      double mean_ang{};
      double sigma_ang{};

      std::ifstream in_file{"input.txt"};
      in_file >> r1;
      in_file >> r2;
      assert(r2 > 0 && r2 < r1);
      in_file >> l_min;
      in_file >> l_max;
      in_file >> step;
      assert(step <= l_max - l_min);
      in_file >> n;
      in_file >> mean_y;
      assert(mean_y < r1);
      in_file >> sigma_y;
      in_file >> mean_ang;
      assert(mean_ang > -M_PI / 2 && mean_ang < M_PI / 2);
      in_file >> sigma_ang;

      std::random_device r;
      std::default_random_engine eng{r()};
      Gen::PartG g{eng, mean_y, sigma_y, mean_ang, sigma_ang, r1};
      std::vector<Ric::Particle> particles{};

      particles.reserve(n);
      std::generate_n(particles.begin(), n, g);

      for (double l{l_min}; l <= l_max; l += step) {
        std::vector<Ric::Particle> transf{};
        transf.reserve(n);
      }
    }

    if (command == 'q') {
      break;
    }
  }
}
