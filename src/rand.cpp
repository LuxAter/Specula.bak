#include "specula/rand.hpp"

#include <limits>
#include <random>

static std::random_device rd;
namespace specula {
std::mt19937 gen(rd());
std::uniform_real_distribution<float> unif_real_dist(0.0f, 1.0f);
std::uniform_int_distribution<std::size_t>
    unif_size_dist(std::numeric_limits<std::size_t>::min(),
                   std::numeric_limits<std::size_t>::max());
} // namespace specula
