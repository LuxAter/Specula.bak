#ifndef SPECULA_IMAGE_IMAGE_HPP_
#define SPECULA_IMAGE_IMAGE_HPP_

#include <cstdint>

namespace specula {
namespace image {
  class Image {
   public:
    Image();
    Image(std::size_t s);
    Image(std::size_t w, std::size_t h);
    virtual ~Image();

    void fill(const uint32_t& c);

    uint32_t& operator()(const std::size_t& i);
    uint32_t operator()(const std::size_t& i) const;
    uint32_t& operator()(const std::size_t& r, const std::size_t& c);
    uint32_t operator()(const std::size_t& r, const std::size_t& c) const;

    std::size_t width_, height_;
    uint32_t* buffer_;
  };
}  // namespace image
}  // namespace specula

#endif  // SPECULA_IMAGE_IMAGE_HPP_
