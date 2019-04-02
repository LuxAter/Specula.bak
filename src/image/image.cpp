#include "image.hpp"

#include <cstdlib>

specula::image::Image::Image() : width_(0), height_(0), buffer_(nullptr) {}
specula::image::Image::Image(std::size_t s)
    : width_(s), height_(s), buffer_(nullptr) {
  buffer_ = (uint32_t*)std::malloc(s * s * sizeof(uint32_t*));
  fill(0xffffff);
}
specula::image::Image::Image(std::size_t w, std::size_t h)
    : width_(w), height_(h), buffer_(nullptr) {
  buffer_ = (uint32_t*)std::malloc(w * h * sizeof(uint32_t*));
  fill(0xffffff);
}

specula::image::Image::~Image() { free(buffer_); }

void specula::image::Image::fill(const uint32_t& c) {
  for (std::size_t i = 0; i < width_ * height_; ++i) {
    buffer_[i] = c;
  }
}

uint32_t& specula::image::Image::operator()(const std::size_t& i) {
  return buffer_[i];
}
uint32_t specula::image::Image::operator()(const std::size_t& i) const {
  return buffer_[i];
}
uint32_t& specula::image::Image::operator()(const std::size_t& r,
                                            const std::size_t& c) {
  return buffer_[(r * width_) + c];
}

uint32_t specula::image::Image::operator()(const std::size_t& r,
                                           const std::size_t& c) const {
  return buffer_[(r * width_) + c];
}
