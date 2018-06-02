#include "render/renderer.hpp"

#include "image.hpp"
#include "render/caster.hpp"
#include "render/options.hpp"
#include "scene.hpp"

#include "basic/vector.hpp"

specula::Image specula::RenderImage(uint32_t width, uint32_t height,
                                    const Scene& scene, const Options& opt) {
  Image img(width, height);
  for (uint32_t x = 0; x < width; ++x) {
    for (uint32_t y = 0; y < height; ++y) {
      double dir_x = (2.0 * (x + 0.5) / static_cast<double>(width) - 1.0) *
                     (width / static_cast<double>(height)) * tan((M_PI / 4.0) / 2.0);
      double dir_y = (1.0 - 2.0 * (y + 0.5) / static_cast<double>(height)) *
                     tan((M_PI / 4.0) / 2.0);
      estl::base::Vec3d dir(dir_x, dir_y, 1);
      dir = Normalize(dir);
      Color c = CastRay({0,0,0}, dir, scene, opt);
      img.SetPixel(x, y, c.r, c.g, c.b);
    }
  }
  return img;
}
