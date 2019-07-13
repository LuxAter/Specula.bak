#include "image/png.hpp"

#include <png.h>

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include "util.hpp"

bool specula::image::write_png(const std::string &file_path, const unsigned &w,
                               const unsigned &h,
                               const std::vector<uint32_t> &pixels) {
  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    error("Failed to create PNG write struct");
    return false;
  }
  png_infop info = png_create_info_struct(png);
  if (!info) {
    error("Failed to create PNG info struct");
    return false;
  }
  if (setjmp(png_jmpbuf(png))) {
    return false;
  }
  FILE *out = fopen(file_path.c_str(), "w");
  if (!out) {
    error("Failed to open file \"{}\"", file_path);
    return false;
  }
  uint8_t **byte_data = (uint8_t **)std::malloc(h * sizeof(uint8_t *));
  if (!byte_data) {
    fclose(out);
    return false;
  }
  for (uint32_t i = 0; i < h; ++i) {
#if COLOR_DEPTH == 16
    byte_data[i] = (uint8_t *)std::malloc(6 * w * sizeof(uint8_t));
#else
    byte_data[i] = (uint8_t *)std::malloc(3 * w * sizeof(uint8_t));
#endif
    if (!byte_data[i]) {
      for (uint32_t j = 0; j < i; ++j) {
        free(byte_data[j]);
      }
      free(byte_data);
      fclose(out);
      return false;
    }
#if COLOR_DEPTH == 16
    std::memset(byte_data[i], 0x00, 6 * w * sizeof(uint8_t));
#else
    std::memset(byte_data[i], 0x00, 3 * w * sizeof(uint8_t));
#endif
    for (uint32_t j = 0; j < w; ++j) {
#if COLOR_DEPTH == 16
      uint32_t id = 6 * j;
      byte_data[i][id + 0] = (pixels[i * w + j] >> 40) & 0xff;
      byte_data[i][id + 1] = (pixels[i * w + j] >> 32) & 0xff;
      byte_data[i][id + 2] = (pixels[i * w + j] >> 24) & 0xff;
      byte_data[i][id + 3] = (pixels[i * w + j] >> 16) & 0xff;
      byte_data[i][id + 4] = (pixels[i * w + j] >> 8) & 0xff;
      byte_data[i][id + 5] = (pixels[i * w + j] >> 0) & 0xff;
#else
      uint32_t id = 3 * j;
      byte_data[i][id + 0] = (pixels[i * w + j] >> 16) & 0xff;
      byte_data[i][id + 1] = (pixels[i * w + j] >> 8) & 0xff;
      byte_data[i][id + 2] = (pixels[i * w + j] >> 0) & 0xff;
#endif
    }
  }
  png_init_io(png, out);
  png_set_IHDR(png, info, w, h, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);
  png_write_image(png, byte_data);
  png_write_end(png, NULL);
  png_free_data(png, info, PNG_FREE_ALL, -1);
  png_destroy_write_struct(&png, (png_infopp)NULL);
  for (uint32_t i = 0; i < h; ++i) {
    free(byte_data[i]);
  }
  free(byte_data);
  fclose(out);
  return true;
}
