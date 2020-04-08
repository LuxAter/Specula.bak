#include "specula/core/imageio.hpp"
#include "global/functions.hpp"
#include "specula/core/spectrum.hpp"

#define cimg_display 0
// #define cimg_use_png 1
// #define cimg_use_jpeg 1
// #define cimg_use_tiff 1
// #define

#include <CImg.h>

std::unique_ptr<specula::RGBSpectrum[]>
specula::read_image(const std::string &name, Point2i *resolution) {
  const cimg_library::CImg<std::uint8_t> image =
      cimg_library::CImg<>(name.c_str()).normalize(0, 255);
  resolution->x = image.width();
  resolution->y = image.height();
  RGBSpectrum *ret = new RGBSpectrum[image.width() * image.height()];
  for (int y = 0; y < image.height(); ++y) {
    for (int x = 0; x < image.width(); ++x) {
      Float c[3];
      c[0] = image(x, y, 0, 0) / 255.0f;
      c[1] = image(x, y, 0, 1) / 255.0f;
      c[2] = image(x, y, 0, 2) / 255.0f;
      ret[y * image.width() + x] = RGBSpectrum::from_rgb(c);
    }
  }
  return std::unique_ptr<RGBSpectrum[]>(ret);
}

void specula::write_image(const std::string &name, const Float *rgb,
                          const Bounds2i &output_bounds,
                          const Point2i &) {
  Vector2i resolution = output_bounds.diagonal();
  cimg_library::CImg<std::uint8_t> image(resolution.x, resolution.y, 1, 3);
  for (int y = 0; y < resolution.y; ++y) {
    for (int x = 0; x < resolution.x; ++x) {
      // TODO: Gamma correction? or does CImg do it for us?
      image(x, y, 0, 0) = (rgb[3 * (y * resolution.x + x) + 0]) * 255.0f;
      image(x, y, 0, 1) = (rgb[3 * (y * resolution.x + x) + 1]) * 255.0f;
      image(x, y, 0, 2) = (rgb[3 * (y * resolution.x + x) + 2]) * 255.0f;
    }
  }
  image.normalize(0x00, 0xff).save(name.c_str());
}
