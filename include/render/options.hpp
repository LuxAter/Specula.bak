#ifndef SPECULA_RENDER_OPTIONS_HPP_
#define SPECULA_RENDER_OPTIONS_HPP_

#include <cstdint>

namespace specula {
  struct Options{
    uint32_t max_depth;
    uint32_t sample_count;
  };
} // namespace specula

#endif  // SPECULA_RENDER_OPTIONS_HPP_
