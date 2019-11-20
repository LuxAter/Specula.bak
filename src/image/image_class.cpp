#include "image/image_class.hpp"

#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <vector>

#include <cstdio>

#include <glm/glm.hpp>

#include "filesystem.hpp"
#include "image/bmp.hpp"
#include "image/jpeg.hpp"
#include "image/png.hpp"
#include "log.hpp"

specula::image::Image::Image(const std::size_t &pix_width,
                             const std::size_t &pix_height)
    : resolution_{pix_width, pix_height},
      buffer_(pix_width * pix_height, glm::vec3{0.0, 0.0, 0.0}) {}
specula::image::Image::Image(const glm::uvec2 &resolution)
    : resolution_(resolution), buffer_(resolution.x * resolution.y) {}

bool specula::image::Image::write(const std::string_view &file) {
  fs::path file_path(file);
  file_path = fs::absolute(file_path);
  if (fs::exists(file_path)) {
    LWARN("File {} already exists, overwriting", file_path);
  } else if (!fs::exists(file_path.parent_path())) {
    LINFO("Creating {}", file_path.parent_path());
    fs::create_directories(file_path.parent_path());
  }
  if (file_path.extension() == ".png") {
    return write_png(file, resolution_, buffer_);
  } else if (file_path.extension() == ".jpeg") {
    return write_jpeg(file, resolution_, buffer_);
  } else if (file_path.extension() == ".bmp") {
    return write_bmp(file, resolution_, buffer_);
  }
  return false;
}

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
