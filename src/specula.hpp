#ifndef SPECULA_SPECULA_HPP_
#define SPECULA_SPECULA_HPP_

#define SPECULA_VERSION_MAJOR 1
#define SPECULA_VERSION_MINOR 0

#include "image/image.hpp"
#include "image/write_png.hpp"

namespace specula {
  int version_major();
  int version_minor();
} // namespace specula

#endif  // SPECULA_SPECULA_HPP_
