#ifndef SPECULA_CORE_FILM_HPP_
#define SPECULA_CORE_FILM_HPP_

#include "core/geometry/common.hpp"
#include "core/geometry/point.hpp"
#include "filter.hpp"
#include "geometry.hpp"
#include "global/compiler.hpp"
#include "global/constants.hpp"
#include "parallel.hpp"
#include "spectrum.hpp"
#include "specula/dev.hpp"
#include "specula/global.hpp"

namespace specula {
struct FilmTilePixel {
  Spectrum contrib_sum = 0.0f;
  Float filter_weight_sum = 0.0f;
};
class Film {
public:
  Film(const Point2i &resolution, const Bounds2f &crop_window,
       std::unique_ptr<Filter> filter, Float diagonal,
       const std::string &filename, Float scale,
       Float max_sample_luminance = INFTY);
  Bounds2i get_sample_bounds() const;
  Bounds2f get_physical_extent() const;
  std::unique_ptr<FilmTile> get_film_tile(const Bounds2i &sample_bounds);

  void merge_film_tile(std::unique_ptr<FilmTile> tile);
  void set_image(const Spectrum *img) const;
  void add_splat(const Point2f &p, Spectrum v);
  void write_image(Float splat_scale = 1.0f);
  void clear();

  const Point2i full_resolution;
  const Float diagonal;
  std::unique_ptr<Filter> filter;
  const std::string filename;
  Bounds2i cropped_pixel_bounds;

private:
  struct Pixel {
    Pixel() { xyz[0] = xyz[1] = xyz[2] = filter_weight_sum = 0; }
    Float xyz[3];
    Float filter_weight_sum;
    AtomicFloat splat_xyz[3];
    Float pad;
  };
  std::unique_ptr<Pixel[]> pixels;
  SPECULA_CONSTEXPR static int filter_table_width = 16;
  Float filter_table[filter_table_width * filter_table_width];
  std::mutex mutex;
  const Float scale;
  const Float max_sample_luminance;

  Pixel &get_pixel(const Point2i &p) {
    CHECK(inside_exclusive(p, cropped_pixel_bounds));
    int width = cropped_pixel_bounds.p_max.x - cropped_pixel_bounds.p_min.x;
    int offset = (p.x - cropped_pixel_bounds.p_min.x) +
                 (p.y - cropped_pixel_bounds.p_min.y) * width;
    return pixels[offset];
  }
};

class FilmTile {
public:
  FilmTile(const Bounds2i &pixel_bounds, const Vector2f &filter_radius,
           const Float *filter_table, int filter_table_size,
           Float max_sample_luminance)
      : pixel_bounds(pixel_bounds), filter_radius(filter_radius),
        inv_filter_radius(1.0 / filter_radius.x, 1.0 / filter_radius.y),
        filter_table(filter_table), filter_table_size(filter_table_size),
        max_sample_luminance(max_sample_luminance) {
    pixels = std::vector<FilmTilePixel>(std::max(0, pixel_bounds.area()));
  }
  void add_sample(const Point2f &film, Spectrum l, Float sample_weight = 1.0f) {
    PROF_FUNC_ARGS(film, l, sample_weight);
    if (l.y() > max_sample_luminance)
      l *= max_sample_luminance / l.y();
    Point2f film_discrete = film - Vector2f(0.5f, 0.5f);
    Point2i p0 = static_cast<Point2i>(ceil(film_discrete - filter_radius));
    Point2i p1 = static_cast<Point2i>(floor(film_discrete + filter_radius)) +
                 Point2i(1, 1);
    p0 = max(p0, pixel_bounds.p_min);
    p1 = min(p1, pixel_bounds.p_max);

    int *ifx = ALLOCA(int, p1.x - p0.x);
    for (int x = p0.x; x < p1.x; ++x) {
      Float fx = std::abs((x - film_discrete.x) * inv_filter_radius.x *
                          filter_table_size);
      ifx[x - p0.x] =
          std::min(static_cast<int>(std::floor(fx)), filter_table_size - 1);
    }
    int *ify = ALLOCA(int, p1.y - p0.y);
    for (int y = p0.y; y < p1.y; ++y) {
      Float fy = std::abs((y - film_discrete.y) * inv_filter_radius.y *
                          filter_table_size);
      ify[y - p0.y] =
          std::min(static_cast<int>(std::floor(fy)), filter_table_size - 1);
    }
    for (int y = p0.y; y < p1.y; ++y) {
      for (int x = p0.x; x < p1.x; ++x) {
        int offset = ify[y - p0.y] * filter_table_size + ifx[x - p0.x];
        Float filter_weight = filter_table[offset];
        FilmTilePixel &pixel = get_pixel(Point2i(x, y));
        pixel.contrib_sum += l * sample_weight * filter_weight;
        pixel.filter_weight_sum += filter_weight;
      }
    }
  }
  FilmTilePixel &get_pixel(const Point2i &p) {
    CHECK(inside_exclusive(p, pixel_bounds));
    int width = pixel_bounds.p_max.x - pixel_bounds.p_min.x;
    int offset =
        (p.x - pixel_bounds.p_min.x) + (p.y - pixel_bounds.p_min.y) * width;
    return pixels[offset];
  }
  const FilmTilePixel &get_pixel(const Point2i &p) const {
    CHECK(inside_exclusive(p, pixel_bounds));
    int width = pixel_bounds.p_max.x - pixel_bounds.p_min.x;
    int offset =
        (p.x - pixel_bounds.p_min.x) + (p.y - pixel_bounds.p_min.y) * width;
    return pixels[offset];
  }
  Bounds2i get_pixel_bounds() const { return pixel_bounds; }

private:
  const Bounds2i pixel_bounds;
  const Vector2f filter_radius, inv_filter_radius;
  const Float *filter_table;
  const int filter_table_size;
  std::vector<FilmTilePixel> pixels;
  const Float max_sample_luminance;
  friend class Film;
};
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_FILM_HPP_ */
