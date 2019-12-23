#include "specula/image.hpp"

#include <string_view>
#include <vector>

#include <glm/glm.hpp>

#include "stb_image_write.hpp"

specula::Image::Image() : buffer_width(0), buffer_height(0), buffer() {}
specula::Image::Image(const unsigned &width, const unsigned &height)
    : buffer_width(width), buffer_height(height),
      buffer(width * height, glm::vec3(0.0f)) {}

std::uint8_t *specula::Image::get_byte_data() const {
  std::uint8_t *byte_data = static_cast<std::uint8_t *>(
      std::malloc(sizeof(std::uint8_t) * 3 * buffer_width * buffer_height));
  for (std::size_t i = 0; i < buffer.size(); i++) {
    std::size_t j = i * 3;
    byte_data[j + 0] = static_cast<std::uint8_t>(buffer[i].r * 255);
    byte_data[j + 1] = static_cast<std::uint8_t>(buffer[i].g * 255);
    byte_data[j + 2] = static_cast<std::uint8_t>(buffer[i].b * 255);
  }
  return byte_data;
}
float *specula::Image::get_float_data() const {
  float *byte_data = static_cast<float *>(
      std::malloc(sizeof(float) * 3 * buffer_width * buffer_height));
  for (std::size_t i = 0; i < buffer.size(); i++) {
    std::size_t j = i * 3;
    byte_data[j + 0] = buffer[i].r;
    byte_data[j + 1] = buffer[i].g;
    byte_data[j + 2] = buffer[i].b;
  }
  return byte_data;
}

bool specula::Image::write(const std::string_view &file_path) {
  int result = 1;
  if (file_path.length() >= 4 &&
      file_path.compare(file_path.length() - 4, 4, ".png") == 0) {
    std::uint8_t *byte_data = get_byte_data();
    result = stbi_write_png(file_path.data(), buffer_width, buffer_height, 3,
                            byte_data, sizeof(std::uint8_t) * 3 * buffer_width);
    free(byte_data);
  } else if (file_path.length() >= 4 &&
             file_path.compare(file_path.length() - 4, 4, ".bmp") == 0) {
    std::uint8_t *byte_data = get_byte_data();
    result = stbi_write_bmp(file_path.data(), buffer_width, buffer_height, 3,
                            byte_data);
    free(byte_data);
  } else if (file_path.length() >= 4 &&
             file_path.compare(file_path.length() - 4, 4, ".tga") == 0) {
    std::uint8_t *byte_data = get_byte_data();
    result = stbi_write_tga(file_path.data(), buffer_width, buffer_height, 3,
                            byte_data);
    free(byte_data);
  } else if (file_path.length() >= 4 &&
             file_path.compare(file_path.length() - 4, 4, ".hdr") == 0) {
    float *byte_data = get_float_data();
    result = stbi_write_hdr(file_path.data(), buffer_width, buffer_height, 3,
                            byte_data);
    free(byte_data);
  } else if (file_path.length() >= 4 &&
             file_path.compare(file_path.length() - 4, 4, ".jpg") == 0) {
    std::uint8_t *byte_data = get_byte_data();
    result = stbi_write_jpg(file_path.data(), buffer_width, buffer_height, 3,
                            byte_data, 100);
    free(byte_data);
  }
  return result == 0;
}