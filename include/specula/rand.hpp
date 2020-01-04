#ifndef SPECULA_RAND_HPP_
#define SPECULA_RAND_HPP_

#include <random>

namespace specula {
extern std::mt19937 gen;
extern std::uniform_real_distribution<float> unif_real_dist;
extern std::uniform_int_distribution<std::size_t> unif_size_dist;
inline float frand() { return unif_real_dist(gen); }
inline float frand(const float &min, const float &max) {
  return unif_real_dist(gen) * (max - min) + min;
}
inline float size_rand() { return unif_size_dist(gen); }
} // namespace specula

#endif // SPECULA_RAND_HPP_
