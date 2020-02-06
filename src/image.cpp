#include "specula/image.hpp"

#include <glm/glm.hpp>

specula::Image::Image(const uint32_t& w, const uint32_t& h,
                      const float& default_r, const float& default_g,
                      const float& default_b)
    : width(w), height(h),
      pixels(width * height, glm::vec3(default_r, default_g, default_b)) {}
specula::Image::Image(const glm::uvec2& dimensions,
                      const glm::vec3& default_pixel)
    : width(dimensions.x), height(dimensions.y),
      pixels(width * height, default_pixel) {}
