#ifndef SPECULA_UUID_HPP_
#define SPECULA_UUID_HPP_

#include <limits>
#include <random>

#include "fmt.hpp"

namespace specula {
namespace uuid {
static std::random_device uuid_rd;
static std::mt19937 uuid_gen(uuid_rd());

inline char convert(const uint8_t &ch) {
  if (ch < 10)
    return static_cast<char>(ch + 48);
  else if (ch < 36)
    return static_cast<char>(ch + 55);
  else
    return static_cast<char>(ch + 61);
}

template <std::size_t A = 8, std::size_t B = 4, std::size_t C = 4,
          std::size_t D = 4, std::size_t E = 12>
inline std::string uuid() {
  std::uniform_int_distribution<uint8_t> dist(0, 62);
  if constexpr (A == 0 && B == 0 && C == 0 && D == 0 && E == 0)
    return std::string();
  else if constexpr (A != 0 && B == 0 && C == 0 && D == 0 && E == 0) {
    std::string res;
    for (std::size_t a = 0; a < A; ++a) {
      res += convert(dist(uuid_gen));
    }
    return res;
  } else if constexpr (A != 0 && B != 0 && C == 0 && D == 0 && E == 0) {
    std::string res;
    for (std::size_t a = 0; a < A; ++a) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t b = 0; b < B; ++b) {
      res += convert(dist(uuid_gen));
    }
    return res;
  } else if constexpr (A != 0 && B != 0 && C != 0 && D == 0 && E == 0) {
    std::string res;
    for (std::size_t a = 0; a < A; ++a) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t b = 0; b < B; ++b) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t c = 0; c < C; ++c) {
      res += convert(dist(uuid_gen));
    }
    return res;
  } else if constexpr (A != 0 && B != 0 && C != 0 && D != 0 && E == 0) {
    std::string res;
    for (std::size_t a = 0; a < A; ++a) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t b = 0; b < B; ++b) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t c = 0; c < C; ++c) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t d = 0; d < D; ++d) {
      res += convert(dist(uuid_gen));
    }
    return res;
  } else {
    std::string res;
    for (std::size_t a = 0; a < A; ++a) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t b = 0; b < B; ++b) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t c = 0; c < C; ++c) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t d = 0; d < D; ++d) {
      res += convert(dist(uuid_gen));
    }
    res += '-';
    for (std::size_t e = 0; e < E; ++e) {
      res += convert(dist(uuid_gen));
    }
    return res;
  }
}
template <typename _T> inline std::string gen() {
  return fmt::format("%u", std::uniform_int_distribution<_T>(
                               std::numeric_limits<_T>::min(),
                               std::numeric_limits<_T>::max())(uuid_gen));
}
} // namespace uuid
} // namespace specula

#endif // SPECULA_UUID_HPP_
