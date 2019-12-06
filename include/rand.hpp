#ifndef SPECULA_RAND_HPP_
#define SPECULA_RAND_HPP_

#include <random>

namespace specula {
extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<float> unif_real_dist;
extern std::uniform_int_distribution<std::size_t> unif_uint_dist;
extern std::uniform_int_distribution<std::uint8_t> unif_uint8_dist;
extern std::uniform_int_distribution<std::uint32_t> unif_uint32_dist;
inline float frand() { return unif_real_dist(gen); }
inline std::size_t urand() { return unif_uint_dist(gen); }
inline std::uint8_t u8rand() { return unif_uint8_dist(gen); }
inline std::uint32_t u32rand() { return unif_uint32_dist(gen); }
} // namespace specula

#endif // SPECULA_RAND_HPP_
