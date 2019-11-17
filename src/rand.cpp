#include "rand.hpp"

#include <random>

namespace specula::rand {
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> unif_rand_dist(0.0f, 1.0f);
} // namespace specula::rand
