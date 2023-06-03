#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>

#include "project.hpp"

int main() {
  double r1{};
  double r2{};
  double l{};
  double mean_y{};
  double sigma_y{};
  double mean_ang{};
  double sigma_ang{};

  std::ifstream in_file{"input.txt"};
  std::ofstream out_init{"outinit.txt"};
  std::ofstream out_fin{"outfin.txt"};

  in_file >> r1;
  in_file >> r2;
  assert(r2 > 0 && r2 < r1);
  in_file >> l;
  in_file >> mean_y;
  assert(mean_y < r1);
  in_file >> sigma_y;
  in_file >> mean_ang;
  assert(mean_ang > -M_PI / 2 && mean_ang < M_PI / 2);
  in_file >> sigma_ang;

  while (true) {
    char command{};
    std::cout << "Comando: ";
    std::cin >> command;
    assert(command == 'm' || command == 'a' || command == 'q' ||
           command == 's');

    if (command == 'm') {
      double l{};
      double y{};
      double r1f{};
      double r2f{};
      double ang{};
      std::cout << "Inserire r1: ";
      std::cin >> r1f;
      std::cout << "Inserire r2: ";
      std::cin >> r2f;
      assert(r2f > 0 && r2f < r1f);
      std::cout << "Inserire l: ";
      std::cin >> l;
      std::cout << "Inserire y0: ";
      std::cin >> y;
      assert(abs(y) < r1f);
      std::cout << "Inserire angolo di partenza (in gradi): ";
      std::cin >> ang;
      ang = (ang / 360.) * 2 * M_PI;
      assert(ang < M_PI / 2 && ang > -M_PI / 2);
      Ric::Point pos{0, y};
      Ric::Particle p{pos, ang};
      Gen::PartM move{r1f, r2f, l};
      move(p);
      std::cout << "Y finale: " << p.position().y << "\n"
                << "Angolo (radianti):" << p.angle() << "\n"
                << "Angolo (gradi): " << ((p.angle() / (2 * M_PI)) * 360)
                << "\n";
      continue;
    }

    if (command == 'a') {
      int n{};
      std::cin >> n;
      std::random_device r;
      std::default_random_engine eng{r()};
      Gen::PartG g{eng, mean_y, sigma_y, mean_ang, sigma_ang, r1};
      Ric::Point def{0, 0};
      Ric::Particle defp{def, 0.};
      std::vector<Ric::Particle> particles{};
      particles.resize(n, defp);
      std::generate_n(particles.begin(), n, g);
      for (int i{0}; i < n; ++i) {
        out_init << particles[i].position().x << " "
                 << particles[i].position().y << " " << particles[i].angle()
                 << "\n";
      }

      Gen::PartM move(r1, r2, l);
      std::for_each_n(particles.begin(), n, move);

      for (int i{0}; i < n; ++i) {
        out_fin << particles[i].position().x << " " << particles[i].position().y
                << " " << particles[i].angle() << "\n";
      }
    }

    if (command == 's') {
      std::string s{};
      std::cin >> s;
      std::vector<Ric::Particle> p{};
      Stats::Sample sample{p};
      sample.read(s);
      Stats::Statistics y{sample.statistics_y()};
      Stats::Statistics ang{sample.statistics_ang()};

      std::cout << "Posizione finale y:\nMedia: " << y.mean << "\nDeviazione standard: " << y.sigma
                << "\nCoefficiente di simmetria: " << y.simm;
      if (y.simm > 0.0000001) {
        std::cout << " (distribuzione asimmetrica positiva)\n";
      }
      if (y.simm < -0.0000001) {
        std::cout << " (distribuzione asimmetrica negativa)\n";
      }
      if (y.simm >= -0.0000001 && y.simm <= 0.0000001) {
        std::cout << " (distribuzione simmetrica)\n";
      }
      std::cout << "Coefficiente di appiattimento: " << y.app;
      if (y.simm > 3.0000001) {
        std::cout << " (distribuzione leptocurtica)\n";
      }
      if (y.simm < 2.9999999) {
        std::cout << " (distribuzione platicurtica)\n";
      }
      if (y.simm >= 2.9999999 && y.simm <= 3.0000001) {
        std::cout << " (distribuzione mesocurtica)\n";
      }

      std::cout << "\nAngolo finale\nMedia: " << ang.mean << "\nDeviazione standard: " << ang.sigma
                << "\nCoefficiente di simmetria: " << ang.simm;
      if (ang.simm > 0.0000001) {
        std::cout << " (distribuzione asimmetrica positiva)\n";
      }
      if (ang.simm < -0.0000001) {
        std::cout << " (distribuzione asimmetrica negativa)\n";
      }
      if (ang.simm >= -0.0000001 && ang.simm <= 0.0000001) {
        std::cout << " (distribuzione simmetrica)\n";
      }
      std::cout << "Coefficiente di appiattimento: " << ang.app;
      if (ang.simm > 3.0000001) {
        std::cout << " (distribuzione leptocurtica)\n";
      }
      if (ang.simm < 2.9999999) {
        std::cout << " (distribuzione platicurtica)\n";
      }
      if (ang.simm >= 2.9999999 && ang.simm <= 3.0000001) {
        std::cout << " (distribuzione mesocurtica)\n";
      }
      std::cout<<"\n";
    }

    if (command == 'q') {
      break;
    }
  }
}
