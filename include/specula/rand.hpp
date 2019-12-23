#ifndef SPECULA_RAND_HPP_
#define SPECULA_RAND_HPP_

#include <random>

namespace specula {
extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<float> unif_real_dist;
extern std::uniform_int_distribution<unsigned> unif_uint_dist;
extern std::uniform_int_distribution<unsigned long> unif_ulong_dist;
inline float frand() { return unif_real_dist(gen); }
inline unsigned urand() { return unif_uint_dist(gen); }
inline unsigned long ulrand() { return unif_ulong_dist(gen); }
} // namespace specula

#endif // SPECULA_RAND_HPP_