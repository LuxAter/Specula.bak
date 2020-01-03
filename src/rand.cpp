#include "specula/rand.hpp"

#include <limits>
#include <random>

static std::random_device rd;
namespace specula {
std::mt19937 gen(rd());
std::uniform_real_distribution<float> unif_real_dist(0.0f, 1.0f);
} // namespace specula