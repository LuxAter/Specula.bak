#include "image/png.hpp"

#include <array>
#include <cstdlib>
#include <cstring>
#include <string_view>
#include <vector>

#include <png.h>

#include <glm/glm.hpp>

#include "log.hpp"

bool specula::image::write_png(const std::string_view &file,
                               const glm::uvec2 &resolution,
                               const std::vector<glm::vec3> &buffer) {
  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    LERROR("Failed to create PNG write struct");
    return false;
  }
  png_infop info = png_create_info_struct(png);
  if (!info) {
    LERROR("Failed to create PNG info struct");
    return false;
  }
  if (setjmp(png_jmpbuf(png))) {
    LERROR("Issue durring png writing");
    return false;
  }
  FILE *out = std::fopen(file.data(), "wb");
  if (!out) {
    LERROR("Failed to open \"{}\" for writting", file);
    return false;
  }
  uint8_t **byte_data =
      (uint8_t **)std::malloc(resolution.y * sizeof(uint8_t *));
  if (!byte_data) {
    LERROR("Failed to allocate memory for byte data");
    fclose(out);
    return false;
  }
  for (std::size_t i = 0; i < resolution.y; ++i) {
    byte_data[i] = (uint8_t *)std::malloc(6 * resolution.x * sizeof(uint8_t));
    if (!byte_data[i]) {
      LERROR("Failed to allocate memory for byte data");
      for (std::size_t j = 0; j < i; ++j) {
        free(byte_data[j]);
      }
      free(byte_data);
      fclose(out);
      return false;
    }
    std::memset(byte_data[i], 0x00, 6 * resolution.x * sizeof(uint8_t));
    for (std::size_t j = 0; j < resolution.x; ++j) {
      uint16_t red =
          static_cast<uint16_t>(buffer[i * resolution.x + j].r * 65535 + 0.5);
      uint16_t green =
          static_cast<uint16_t>(buffer[i * resolution.x + j].g * 65535 + 0.5);
      uint16_t blue =
          static_cast<uint16_t>(buffer[i * resolution.x + j].b * 65535 + 0.5);
      std::size_t id = 6 * j;
      byte_data[i][id] = static_cast<uint8_t>((red >> 8) & 0xff);
      byte_data[i][id + 1] = static_cast<uint8_t>(red & 0xff);
      byte_data[i][id + 2] = static_cast<uint8_t>((green >> 8) & 0xff);
      byte_data[i][id + 3] = static_cast<uint8_t>(green & 0xff);
      byte_data[i][id + 4] = static_cast<uint8_t>((blue >> 8) & 0xff);
      byte_data[i][id + 5] = static_cast<uint8_t>(blue & 0xff);
    }
  }
  png_init_io(png, out);
  png_set_IHDR(png, info, resolution.x, resolution.y, 16, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);
  png_write_image(png, byte_data);
  png_write_end(png, NULL);
  png_free_data(png, info, PNG_FREE_ALL, -1);
  png_destroy_write_struct(&png, (png_infopp)NULL);
  for (std::size_t i = 0; i < resolution.y; ++i) {
    free(byte_data[i]);
  }
  free(byte_data);
  LINFO("Wrote image to \"{}\"", file);
  return true;
}
