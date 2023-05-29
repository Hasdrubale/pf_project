#include "project.hpp"

Stats::Sample::Sample(std::vector<Ric::Particle> particles)
    : particles_{particles} {}

Stats::Statistics Stats::Sample::statistics_y() {
    
}

Stats::Statistics Stats::Sample::statistics_ang() {}