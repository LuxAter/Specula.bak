#ifndef SPECULA_IMAGE_HPP_
#define SPECULA_IMAGE_HPP_

#include <string_view>
#include <vector>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

namespace specula {
class Image {
public:
  Image();
  Image(const unsigned &width, const unsigned &height);

  inline void set(const unsigned &id, const glm::vec3 &v) { buffer[id] = v; }
  inline void set(const unsigned &x, const unsigned &y, const glm::vec3 &v) {
    buffer[y * buffer_width + x] = v;
  }

  inline glm::vec3 &operator()(const unsigned &x, const unsigned &y) {
    return buffer[y * buffer_width + x];
  }
  inline const glm::vec3 &operator()(const unsigned &x,
                                     const unsigned &y) const {
    return buffer[y * buffer_width + x];
  }

  bool write(const std::string_view &file_path);

private:
  std::uint8_t *get_byte_data() const;
  float *get_float_data() const;

  unsigned buffer_width, buffer_height;
  std::vector<glm::vec3> buffer;
};

} // namespace specula

#endif
