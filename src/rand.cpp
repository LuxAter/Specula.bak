#include "specula/rand.hpp"

#include <limits>
#include <random>

namespace specula {
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> unif_real_dist(0.0f, 1.0f);
std::uniform_int_distribution<unsigned>
    unif_uint_dist(0, std::numeric_limits<unsigned>::max());
std::uniform_int_distribution<unsigned long>
    unif_ulong_dist(0, std::numeric_limits<unsigned long>::max());
} // namespace specula