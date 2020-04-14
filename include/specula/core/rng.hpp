#ifndef SPECULA_CORE_RNG_HPP_
#define SPECULA_CORE_RNG_HPP_

#include "specula/global.hpp"

#define PCG32_DEFAULT_STATE 0x853c49e6748fea9bull
#define PCG32_DEFAULT_STREAM 0xda3e39cb94b95bdbull
#define PCG32_MULT 0x5851f42d4c957f2dull

namespace specula {
static const double double_one_minus_epsilon = 0.99999999999999989;
static const float float_one_minus_epsilon = 0.99999994;

#ifdef SPECULA_DOUBLE_PRECISION
static const Float one_minus_epsilon = double_one_minus_epsilon;
#else
static const Float one_minus_epsilon = float_one_minus_epsilon;
#endif

class Rng {
public:
  Rng() : state(PCG32_DEFAULT_STATE), inc(PCG32_DEFAULT_STREAM) {}
  Rng(uint64_t sequence_index) { set_sequence(sequence_index); }
  void set_sequence(uint64_t sequence_index) {
    state = 0u;
    inc = (sequence_index << 1u) | 1u;
    uniform_uint32();
    state += PCG32_DEFAULT_STATE;
    uniform_uint32();
  }
  uint32_t uniform_uint32() {
    uint64_t old_state = state;
    state = old_state * PCG32_MULT + inc;
    uint32_t xor_shifted =
        static_cast<uint32_t>(((old_state >> 18u) ^ old_state) >> 27u);
    uint32_t rot = static_cast<uint32_t>(old_state >> 59u);
    return (xor_shifted >> rot) | (xor_shifted << ((~rot + 1u) & 31));
  }
  uint32_t uniform_uint32(uint32_t b) {
    uint32_t threshold = (~b + 1u) % b;
    while (true) {
      uint32_t r = uniform_uint32();
      if (r >= threshold)
        return r % b;
    }
  }
  Float uniform_float() {
    return std::min(one_minus_epsilon,
                    Float(uniform_uint32() * 2.3283064365386963e-10f));
  }
  template <typename Iterator> void shuffle(Iterator begin, Iterator end) {
    for (Iterator it = end - 1; it > begin; --it) {
      std::iter_swap(
          it, begin + uniform_uint32(static_cast<uint32_t>(it - begin + 1)));
    }
  }

  void advance(int64_t idelta) {
    uint64_t cur_mult = PCG32_MULT, cur_plus = inc, acc_mult = 1u,
             acc_plus = 0u, delta = static_cast<uint64_t>(idelta);
    while (delta > 0) {
      if (delta & 1) {
        acc_mult *= cur_mult;
        acc_plus = acc_plus * cur_mult + cur_plus;
      }
      cur_plus = (cur_mult + 1) * cur_plus;
      cur_mult *= cur_mult;
      delta /= 2;
    }
    state = acc_mult * state + acc_plus;
  }

  int64_t operator-(const Rng &other) const {
    CHECK_EQ(inc, other.inc);
    uint64_t cur_mult = PCG32_MULT, cur_plus = inc, cur_state = other.state,
             the_bit = 1u, distance = 0u;
    while (state != cur_state) {
      if ((state & the_bit) != (cur_state & the_bit)) {
        cur_state = cur_state * cur_mult + cur_plus;
        distance |= the_bit;
      }
      CHECK_EQ(state & the_bit, cur_state & the_bit);
      the_bit <<= 1;
      cur_plus = (cur_mult + 1ull) * cur_plus;
      cur_mult *= cur_mult;
    }
    return static_cast<int64_t>(distance);
  }

private:
  uint64_t state, inc;
};
} // namespace specula

#endif // SPECULA_CORE_RNG_HPP_
