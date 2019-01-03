#ifndef SPECULA_IMAGE_HPP_
#define SPECULA_IMAGE_HPP_

#include <png.h>
#include <array>
#include <vector>

namespace specula {
namespace image {
  class Image {
   public:
    Image(const std::size_t& res, const double& ratio=16.0/9.0);
    Image(const std::size_t& width, const std::size_t& height);
    Image(const Image& copy);
    ~Image();

    inline std::size_t Width() const { return size_[0]; }
    inline std::size_t Height() const { return size_[1]; }
    inline std::array<std::size_t, 2> Size() const { return size_; }

    void Pixel(const std::size_t& x, const std::size_t& y, unsigned pixel);
    void Fill(unsigned pixel);

    void WritePng(const std::string& file);

   private:
    std::array<std::size_t, 2> size_;
    std::vector<unsigned> pixel_data_;
  };
}  // namespace image
}  // namespace specula

#endif  // SPECULA_IMAGE_HPP_
