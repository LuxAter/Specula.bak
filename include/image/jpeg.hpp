#ifndef SPECULA_IMAGE_JPEG_HPP_
#define SPECULA_IMAGE_JPEG_HPP_

#include <array>
#include <cstdlib>
#include <string_view>
#include <vector>

#include <glm/glm.hpp>

namespace specula {
namespace image {
bool write_jpeg(const std::string_view &file, const glm::uvec2 &resolutin,
                const std::vector<glm::vec3> &buffer);
} // namespace image
} // namespace specula

#endif // SPECULA_IMAGE_JPEG_HPP_
