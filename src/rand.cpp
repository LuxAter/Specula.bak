#include "rand.hpp"

#include <random>

namespace specula::rand {
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> unif_rand_dist(0.0f, 1.0f);
std::uniform_int_distribution<std::size_t>
    unif_int_dist(0, std::numeric_limits<std::size_t>::max());
} // namespace specula::rand
