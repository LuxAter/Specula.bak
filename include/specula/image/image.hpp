#ifndef SPECULA_IMAGE_IMAGE_HPP_
#define SPECULA_IMAGE_IMAGE_HPP_

#include <array>
#include <string>
#include <vector>

#include <png.h>

namespace specula {
class Image {
public:
  explicit Image(const std::array<std::size_t, 2> &resolution);

  inline std::array<double, 3> &operator()(const std::size_t &x,
                                           const std::size_t &y) {
    return pixels_[y * resolution_[1] + x];
  }
  bool write(const std::string &filename) const;

  bool write_png(const std::string &filename) const;
  bool write_jpeg(const std::string &filename) const;
  bool write_bmp(const std::string &filename) const;

private:
  std::array<std::size_t, 2> resolution_;
  std::vector<std::array<double, 3>> pixels_;
};
} // namespace specula

#endif // SPECULA_IMAGE_IMAGE_HPP_
