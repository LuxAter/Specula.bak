#include "image/image_class.hpp"

#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <vector>

#include <cstdio>

#include "filesystem.hpp"
#include "image/bmp.hpp"
#include "image/jpeg.hpp"
#include "image/png.hpp"
#include "log.hpp"
#include "math.hpp"

specula::image::Image::Image(const std::size_t &pix_width,
                             const std::size_t &pix_height)
    : resolution_{pix_width, pix_height},
      buffer_(pix_width * pix_height * 3.0) {}
specula::image::Image::Image(const glm::uvec2 &resolution)
    : resolution_(resolution), buffer_(resolution.x * resolution.y) {}

bool specula::image::Image::write(const fs::path &file) {
  fs::path file_path = fs::absolute(file);
  if (fs::exists(file_path)) {
    LWARN("File {} already exists, overwriting", file_path);
  } else if (!fs::exists(file_path.parent_path())) {
    LINFO("Creating {}", file_path.parent_path());
    fs::create_directories(file_path.parent_path());
  }
  if (file_path.extension() == ".png") {
    return write_png(file_path.string(), resolution_, buffer_);
  } else if (file_path.extension() == ".jpeg") {
    return write_jpeg(file_path.string(), resolution_, buffer_);
  } else if (file_path.extension() == ".bmp") {
    return write_bmp(file_path.string(), resolution_, buffer_);
  }
  return false;
}

void specula::image::Image::normalize() {
  float min_v = INFINITY, max_v = -INFINITY;
  for (std::size_t i = 0; i < buffer_.size(); i += 3) {
    min_v = std::min(min_v, std::min(buffer_[i + 0],
                                     std::min(buffer_[i + 1], buffer_[i + 2])));
    max_v = std::max(max_v, std::max(buffer_[i + 0],
                                     std::max(buffer_[i + 1], buffer_[i + 2])));
  }
  float diff = 1.0f / (max_v - min_v);
  for (std::size_t i = 0; i < buffer_.size(); ++i) {
    buffer_[i] = (buffer_[i] - min_v) * diff;
  }
}
void specula::image::Image::abs() {
  for (std::size_t i = 0; i < buffer_.size(); ++i) {
    buffer_[i] = glm::abs(buffer_[i]);
  }
}
