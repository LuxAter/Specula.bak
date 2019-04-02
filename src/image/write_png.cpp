#include "write_png.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <png.h>

#include "image.hpp"

bool specula::image::write_png(const std::string& file, const Image& img) {
  FILE* out = fopen(file.c_str(), "wb");
  if (!out) return false;

  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fclose(out);
    return false;
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(out);
    return false;
  }
  if (setjmp(png_jmpbuf(png))) {
    fclose(out);
    return false;
  }
  uint8_t** byte_data = (uint8_t**)std::malloc(img.height_ * sizeof(uint8_t*));
  for (std::size_t r = 0; r < img.height_; ++r) {
    byte_data[r] = (uint8_t*)std::malloc(6 * img.width_ * sizeof(uint8_t));
  }
  for (std::size_t r = 0; r < img.height_; ++r) {
    for (std::size_t c = 0; c < img.width_; ++c) {
      uint32_t rgb = img(r, c);
      uint32_t red = static_cast<double>((rgb >> 16) & 0xff) * 0xff + 0.5;
      uint32_t green = static_cast<double>((rgb >> 8) & 0xff) * 0xff + 0.5;
      uint32_t blue = static_cast<double>((rgb >> 0) & 0xff) * 0xff + 0.5;
      std::size_t id = 6 * c;
      byte_data[r][id] =
          static_cast<uint8_t>(std::floor(static_cast<double>(red) / 256.0));
      byte_data[r][id + 1] = static_cast<uint8_t>(red % 256);
      byte_data[r][id + 2] =
          static_cast<uint8_t>(std::floor(static_cast<double>(green) / 256.0));
      byte_data[r][id + 3] = static_cast<uint8_t>(green % 256);
      byte_data[r][id + 4] =
          static_cast<uint8_t>(std::floor(static_cast<double>(blue) / 256.0));
      byte_data[r][id + 5] = static_cast<uint8_t>(blue % 256);
    }
  }
  png_init_io(png, out);
  png_set_IHDR(png, info, img.width_, img.height_, 16, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);
  png_write_image(png, byte_data);
  png_write_end(png, NULL);
  png_free_data(png, info, PNG_FREE_ALL, -1);
  png_destroy_write_struct(&png, (png_infopp)NULL);

  fclose(out);
  return true;
}
