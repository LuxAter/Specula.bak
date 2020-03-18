#ifndef SPECULA_GLOBAL_RAND_HPP_
#define SPECULA_GLOBAL_RAND_HPP_

#include <limits>
#include <random>

namespace specula {
class RandomGenerator {
public:
  inline static RandomGenerator *get() {
    if (instance == nullptr)
      instance = new RandomGenerator();
    return instance;
  }

  void seed(std::uint32_t seed) { generator.seed(seed); }

  template <typename T> inline T rand();
  template <typename T> inline T rand(const T &min_v, const T &max_v);

private:
  static RandomGenerator *instance;
  inline RandomGenerator() {
    std::random_device rd;
    generator = std::mt19937_64(rd());
    uint64_dist = std::uniform_int_distribution<std::uint64_t>(
        0, std::numeric_limits<std::uint64_t>::max());
    double_dist = std::uniform_real_distribution<double>(0.0, 1.0);
  }
  std::mt19937_64 generator;
  std::uniform_int_distribution<std::uint64_t> uint64_dist;
  std::uniform_real_distribution<double> double_dist;
};
typedef RandomGenerator RNG;

template <> inline float RandomGenerator::rand() {
  return double_dist(generator);
}
template <> inline double RandomGenerator::rand() {
  return double_dist(generator);
}
template <> inline std::uint32_t RandomGenerator::rand() {
  std::uint64_t rand_val = uint64_dist(generator);
  std::uint32_t xor_shifted =
      static_cast<std::uint32_t>(((rand_val >> 18u) ^ rand_val) >> 27u);
  std::uint32_t rot = static_cast<std::uint32_t>(rand_val >> 59u);
  return (xor_shifted >> rot) | (xor_shifted << ((~rot + 1u) & 31));
}
template <> inline std::uint64_t RandomGenerator::rand() {
  return uint64_dist(generator);
}
template <>
inline float RandomGenerator::rand(const float &min_v, const float &max_v) {
  return (max_v - min_v) * static_cast<float>(double_dist(generator)) + min_v;
}
template <>
inline double RandomGenerator::rand(const double &min_v, const double &max_v) {
  return (max_v - min_v) * double_dist(generator) + min_v;
}
template <>
inline std::uint32_t RandomGenerator::rand(const std::uint32_t &min_v,
                                           const std::uint32_t &max_v) {
  std::uint64_t rand_val = uint64_dist(generator);
  std::uint32_t xor_shifted =
      static_cast<std::uint32_t>(((rand_val >> 18u) ^ rand_val) >> 27u);
  std::uint32_t rot = static_cast<std::uint32_t>(rand_val >> 59u);
  return (max_v - min_v) *
             ((xor_shifted >> rot) | (xor_shifted << ((~rot + 1u) & 31))) +
         min_v;
}
template <>
inline std::uint64_t RandomGenerator::rand(const std::uint64_t &min_v,
                                           const std::uint64_t &max_v) {
  return (max_v - min_v) * uint64_dist(generator) + min_v;
}
} // namespace specula

#endif /* end of include guard: SPECULA_GLOBAL_RAND_HPP_ */
