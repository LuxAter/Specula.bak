#include "image/image_class.hpp"

#include <cstdint>
#include <cstdlib>
#include <string_view>
#include <vector>

#include <cstdio>

#include "util/util.hpp"

specula::image::Image::Image(const std::size_t &pix_width,
                             const std::size_t &pix_height)
    : resolution_{pix_width, pix_height}, buffer_(pix_width * pix_height) {}
specula::image::Image::Image(const Size<std::size_t> &resolution)
    : resolution_(resolution), buffer_(resolution.w * resolution.h) {}

bool specula::image::Image::write(const std::string_view &file) {
  std::string_view file_ext =
      file.substr(file.rfind('.'), file.size() - file.rfind('.'));
  if (file_ext == ".png") {
    return write_png(file);
  } else if (file_ext == ".jpeg") {
    return write_jpeg(file);
  } else if (file_ext == ".bmp") {
    return write_bmp(file);
  }
  return false;
}

bool specula::image::Image::write_png(const std::string_view &file) {
  // linfo("Writing image to \"%s\"", filename.c_str());
  // png_structp png =
  //     png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  // if (!png) {
  //   lerror("Failed to create PNG write struct");
  //   return false;
  // }
  // png_infop info = png_create_info_struct(png);
  // if (!info) {
  //   lerror("Failed to create PNG info struct");
  //   return false;
  // }
  // if (setjmp(png_jmpbuf(png))) {
  //   lerror("Issue durring png writing");
  //   return false;
  // }
  // FILE *out = std::fopen(filename.c_str(), "wb");
  // if (!out) {
  //   lerror("Failed to open \"%s\" for writting", filename.c_str());
  //   return false;
  // }
  // uint8_t **byte_data =
  //     (uint8_t **)std::malloc(resolution_[1] * sizeof(uint8_t *));
  // if (!byte_data) {
  //   lerror("Failed to allocate memory for byte data");
  //   fclose(out);
  //   return false;
  // }
  // for (std::size_t i = 0; i < resolution_[1]; ++i) {
  //   byte_data[i] = (uint8_t *)std::malloc(6 * resolution_[0] * sizeof(uint8_t));
  //   if (!byte_data[i]) {
  //     lerror("Failed to allocate memory for byte data");
  //     for (std::size_t j = 0; j < i; ++j) {
  //       free(byte_data[j]);
  //     }
  //     free(byte_data);
  //     fclose(out);
  //     return false;
  //   }
  //   std::memset(byte_data[i], 0x00, 6 * resolution_[0] * sizeof(uint8_t));
  //   for (std::size_t j = 0; j < resolution_[0]; ++j) {
  //     uint16_t red = static_cast<uint16_t>(
  //         pixels_[i * resolution_[0] + j][0] * 65535 + 0.5);
  //     uint16_t green = static_cast<uint16_t>(
  //         pixels_[i * resolution_[0] + j][1] * 65535 + 0.5);
  //     uint16_t blue = static_cast<uint16_t>(
  //         pixels_[i * resolution_[0] + j][2] * 65535 + 0.5);
  //     std::size_t id = 6 * j;
  //     byte_data[i][id] = static_cast<uint8_t>((red >> 8) & 0xff);
  //     byte_data[i][id + 1] = static_cast<uint8_t>(red & 0xff);
  //     byte_data[i][id + 2] = static_cast<uint8_t>((green >> 8) & 0xff);
  //     byte_data[i][id + 3] = static_cast<uint8_t>(green & 0xff);
  //     byte_data[i][id + 4] = static_cast<uint8_t>((blue >> 8) & 0xff);
  //     byte_data[i][id + 5] = static_cast<uint8_t>(blue & 0xff);
  //   }
  // }
  // png_init_io(png, out);
  // png_set_IHDR(png, info, resolution_[0], resolution_[1], 16,
  //              PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
  //              PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  // png_write_info(png, info);
  // png_write_image(png, byte_data);
  // png_write_end(png, NULL);
  // png_free_data(png, info, PNG_FREE_ALL, -1);
  // png_destroy_write_struct(&png, (png_infopp)NULL);
  // for (std::size_t i = 0; i < resolution_[1]; ++i) {
  //   free(byte_data[i]);
  // }
  // free(byte_data);
  // lsuccess("Wrote image to \"%s\"", filename.c_str());
  return true;
}
bool specula::image::Image::write_jpeg(const std::string_view &file) {
  return true;
}
bool specula::image::Image::write_bmp(const std::string_view &file) {
  return true;
}
