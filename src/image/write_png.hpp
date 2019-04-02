#ifndef SPECULA_IMAGE_PNG_WRITE_HPP_
#define SPECULA_IMAGE_PNG_WRITE_HPP_

#include <string>

#include <png.h>

#include "image.hpp"


namespace specula {
  namespace image {
    bool write_png(const std::string& file, const Image& img);
  } // namespace image
} // namespace specula

#endif  // SPECULA_IMAGE_PNG_WRITE_HPP_
