#include "image/img.hpp"

#include <algorithm>
#include <cstdint>
#include <vector>

#include "image/png.hpp"

specula::image::Image::Image() : width(0), height(0), pixels() {}
specula::image::Image::Image(const unsigned &w, const unsigned &h)
    : width(w), height(h), pixels(w * h) {}

bool specula::image::Image::save(const std::string &file) {
  return write_png(file, width, height, pixels);
}
