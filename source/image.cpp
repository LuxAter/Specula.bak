#include "image.hpp"

#include <array>
#include <cmath>
#include <vector>

#include <png.h>
#include <estl/logger.hpp>

specula::image::Image::Image(const std::size_t& res, const double& ratio) {
  if (res == 240) {
    size_ = {{426, 240}};
  } else if (res == 360) {
    size_ = {{640, 360}};
  } else if (res == 480) {
    size_ = {{854, 480}};
  } else if (res == 720) {
    size_ = {{1280, 720}};
  } else if (res == 1080) {
    size_ = {{1920, 1080}};
  } else if (res == 1440) {
    size_ = {{2560, 1440}};
  } else if (res == 2160) {
    size_ = {{3840, 2160}};
  } else {
    size_ = {{static_cast<std::size_t>(res * ratio), res}};
  }
  pixel_data_ = std::vector<unsigned>(size_[0] * size_[1]);
}
specula::image::Image::Image(const std::size_t& width,
                             const std::size_t& height)
    : size_{{width, height}}, pixel_data_(width * height) {}
specula::image::Image::Image(const Image& copy)
    : size_(copy.size_), pixel_data_(copy.pixel_data_) {}
specula::image::Image::~Image() {}

void specula::image::Image::Pixel(const std::size_t& x, const std::size_t& y,
                                  unsigned pixel) {
  pixel_data_[y * size_[0] + x] = pixel;
}
void specula::image::Image::Fill(unsigned pixel) {
  pixel_data_ = std::vector<unsigned>(size_[0] * size_[1], pixel);
}

void specula::image::Image::WritePng(const std::string& file) {
  FILE* out = fopen(file.c_str(), "wb");
  if (!out) {
    estl::logger::Warning("Failed to open \"%s\"", file.c_str());
    return;
  }
  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fclose(out);
    estl::logger::Warning("Failed to construct PNG write struct");
    return;
  }
  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(out);
    estl::logger::Warning("Failed to construct PNG info struct");
    return;
  }
  if (setjmp(png_jmpbuf(png))) {
    fclose(out);
    estl::logger::Warning("Error in PNG writing");
    return;
  }
  uint8_t** byte_data = (png_bytepp)malloc(size_[1] * sizeof(png_bytep));
  for (uint32_t i = 0; i < size_[1]; ++i) {
    byte_data[i] = (png_bytep)malloc(6 * size_[0] * sizeof(png_byte));
  }
  for (uint32_t y = 0; y < size_[1]; ++y) {
    for (uint32_t x = 0; x < size_[0]; ++x) {
      uint32_t red = ((pixel_data_[y * size_[0] + x] >> 16) & 0XFF) * 256;
      uint32_t green = ((pixel_data_[y * size_[0] + x] >> 8) & 0XFF) * 256;
      uint32_t blue = ((pixel_data_[y * size_[0] + x]) & 0XFF) * 256;
      uint32_t id = x * 6;
      byte_data[y][id] = (uint8_t)(floor((double)red / 256.0));
      byte_data[y][id + 1] = (uint8_t)(red % 256);
      byte_data[y][id + 2] = (uint8_t)(floor((double)green / 256.0));
      byte_data[y][id + 3] = (uint8_t)(green % 256);
      byte_data[y][id + 4] = (uint8_t)(floor((double)blue / 256.0));
      byte_data[y][id + 5] = (uint8_t)(blue % 256);
    }
  }
  png_init_io(png, out);
  png_set_IHDR(png, info, size_[0], size_[1], 16, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);
  png_write_image(png, byte_data);
  png_write_end(png, NULL);
  png_free_data(png, info, PNG_FREE_ALL, -1);
  png_destroy_write_struct(&png, (png_infopp)NULL);
  fclose(out);
}
