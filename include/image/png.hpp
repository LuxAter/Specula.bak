#ifndef SPECULA_IMAGE_PNG_HPP__
#define SPECULA_IMAGE_PNG_HPP__

#include <png.h>

#include <cstdint>
#include <string>
#include <vector>

namespace specula {
namespace image {
bool write_png(const std::string &file_path, const unsigned &w,
               const unsigned &h, const std::vector<uint32_t> &pixels);
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_PNG_HPP__
