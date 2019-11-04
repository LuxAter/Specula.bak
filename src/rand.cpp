#include "rand.hpp"

#include <random>

namespace specula::rand {
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> frand(0.0, 1.0);
} // namespace specula::rand