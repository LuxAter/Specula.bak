#ifndef SPECULA_IMAGE_CLASS_HPP_
#define SPECULA_IMAGE_CLASS_HPP_

#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <vector>

#include "../util/util.hpp"

namespace specula {
namespace image {
class Image {
public:
  Image(const std::size_t &pix_width, const std::size_t &pix_height);
  Image(const Size<std::size_t> &resolution);
  bool write(const std::string_view &file);

private:
  bool write_png(const std::string_view &file);
  bool write_jpeg(const std::string_view &file);
  bool write_bmp(const std::string_view &file);

  Size<std::size_t> resolution_;
  std::vector<std::uint32_t> buffer_;
};
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_CLASS_HPP_
