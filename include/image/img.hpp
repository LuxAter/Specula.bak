#ifndef SPECULA_IMAGE_IMG_HPP_
#define SPECULA_IMAGE_IMG_HPP_

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace specula {
namespace image {
class Image {
public:
  Image();
  Image(const unsigned &w, const unsigned &h);

  bool save(const std::string &file);

  unsigned width, height;
  std::vector<uint32_t> pixels;

private:
};
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_IMG_HPP_
