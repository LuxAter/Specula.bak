#include "specula/core/film.hpp"
#include "core/geometry/common.hpp"
#include "core/spectrum/common.hpp"

specula::Film::Film(const Point2i &resolution, const Bounds2f &crop_window,
                    std::unique_ptr<Filter> filter, Float diagonal,
                    const std::string &filename, Float scale,
                    Float max_sample_luminance)
    : full_resolution(resolution), diagonal(diagonal * 0.001),
      filter(std::move(filter)), filename(filename), scale(scale),
      max_sample_luminance(max_sample_luminance) {
  cropped_pixel_bounds =
      Bounds2i(Point2i(std::ceil(full_resolution.x * crop_window.p_min.x),
                       std::ceil(full_resolution.y * crop_window.p_min.y)),
               Point2i(std::ceil(full_resolution.x * crop_window.p_max.x),
                       std::ceil(full_resolution.y * crop_window.p_max.y)));
  LINFO("Created film with full resolution {}. Crop window of {} -> "
        "cropped_pixel_bounds {}",
        resolution, crop_window, cropped_pixel_bounds);
  pixels = std::unique_ptr<Pixel[]>(new Pixel[cropped_pixel_bounds.area()]);
  PROF_COUNTER("Memory", "Film Pixels",
               cropped_pixel_bounds.area() * sizeof(Pixel));

  int offset = 0;
  for (int y = 0; y < filter_table_width; ++y) {
    for (int x = 0; x < filter_table_width; ++x) {
      Point2f p;
      p.x = (x + 0.5f) * filter->radius.x / filter_table_width;
      p.y = (y + 0.5f) * filter->radius.y / filter_table_width;
      filter_table[offset] = filter->evaluate(p);
    }
  }
}
specula::Bounds2i specula::Film::get_sample_bounds() const {
  Bounds2f float_bounds(floor(Point2f(cropped_pixel_bounds.p_min) +
                              Vector2f(0.5f, 0.5f) - filter->radius),
                        ceil(Point2f(cropped_pixel_bounds.p_max) -
                             Vector2f(0.5f, 0.5f) + filter->radius));
  return static_cast<Bounds2i>(float_bounds);
}
specula::Bounds2f specula::Film::get_physical_extent() const {
  Float aspect = static_cast<Float>(full_resolution.y) /
                 static_cast<Float>(full_resolution.x);
  Float x = std::sqrt(diagonal * diagonal / (1 + aspect * aspect));
  Float y = aspect * x;
  return Bounds2f(Point2f(-x / 2, -y / 2), Point2f(x / 2, y / 2));
}
std::unique_ptr<specula::FilmTile>
specula::Film::get_film_tile(const Bounds2i &sample_bounds) {
  Vector2f half_pixel = Vector2f(0.5f, 0.5f);
  Bounds2f float_bounds = static_cast<Bounds2f>(sample_bounds);
  Point2i p0 = static_cast<Point2i>(
      ceil(float_bounds.p_min - half_pixel - filter->radius));
  Point2i p1 = static_cast<Point2i>(
                   floor(float_bounds.p_max - half_pixel + filter->radius)) +
               Point2i(1, 1);
  Bounds2i tile_pixel_bounds =
      intersect(Bounds2i(p0, p1), cropped_pixel_bounds);
  return std::unique_ptr<FilmTile>(
      new FilmTile(tile_pixel_bounds, filter->radius, filter_table,
                   filter_table_width, max_sample_luminance));
}

void specula::Film::merge_film_tile(std::unique_ptr<FilmTile> tile){
  PROF_FUNC();
  LINFO("Merging film tile {}", tile->pixel_bounds);
  std::lock_guard<std::mutex> lock(mutex);
  for(Point2i pixel : tile->get_pixel_bounds()) {
    const FilmTilePixel & tile_pixel = tile->get_pixel(pixel);
    Pixel &merge_pixel = get_pixel(pixel);
    Float xyz[3];
    tile_pixel.contrib_sum.to_xyz(xyz);
    merge_pixel.xyz[0] += xyz[0];
    merge_pixel.xyz[1] += xyz[1];
    merge_pixel.xyz[2] += xyz[2];
    merge_pixel.filter_weight_sum += tile_pixel.filter_weight_sum;
  }
}
void specula::Film::set_image(const Spectrum *img) const{
  int n_pixels = cropped_pixel_bounds.area();
  for(int i = 0; i < n_pixels; ++i) {
    Pixel &p = pixels[i];
    img[i].to_xyz(p.xyz);
    p.filter_weight_sum = 1;
    p.splat_xyz[0] = p.splat_xyz[1] = p.splat_xyz[2] = 0;
  }
}
void specula::Film::add_splat(const Point2f &p, Spectrum v){
  PROF_FUNC();
  if(v.has_nans()) {
    LERROR("Ignoring splatted spectrum with NaN values at {}", p);
    return;
  } else if(v.y() < 0.0f) {
    LERROR("Ignoring splatted spectrum with negative luminance {} at {}", v.y(), p);
    return;
  } else if(std::isinf(v.y())) {
    LERROR("Ignoring splatted spectrum with infinite luminance at {}", p);
    return;
  }

  Point2i pi = Point2i(floor(p));
  if(!inside_exclusive(pi, cropped_pixel_bounds)) return;
  if(v.y() > max_sample_luminance) v *= max_sample_luminance / v.y();
  Float xyz[3];
  v.to_xyz(xyz);
  Pixel&pixel = get_pixel(pi);
  pixel.splat_xyz[0].add(xyz[0]);
  pixel.splat_xyz[1].add(xyz[1]);
  pixel.splat_xyz[2].add(xyz[2]);
}
void specula::Film::write_image(Float splat_scale){
  LINFO("Converting image to RGB and computing final weighted pixel values");
  std::unique_ptr<Float[]> rgb(new Float[3 * cropped_pixel_bounds.area()]);
  int offset = 0;
  for(Point2i p : cropped_pixel_bounds){
    Pixel &pixel = get_pixel(p);
    xyz_to_rgb(pixel.xyz, &rgb[3 * offset]);
    Float filter_weight_sum = pixel.filter_weight_sum;
    if(filter_weight_sum != 0.0f) {
      Float inv_wt = 1.0f / filter_weight_sum;
      rgb[3 * offset] = std::max(0.0f, rgb[3 * offset] * inv_wt);
      rgb[3 * offset + 1] = std::max(0.0f, rgb[3 * offset + 1] * inv_wt);
      rgb[3 * offset + 2] = std::max(0.0f, rgb[3 * offset + 2] * inv_wt);
    }
    Float splat_rgb[3];
    Float splat_xyz[3] = {pixel.splat_xyz[0], pixel.splat_xyz[1], pixel.splat_xyz[2]};
    xyz_to_rgb(splat_xyz, splat_rgb);
    rgb[3 * offset] += splat_scale * splat_rgb[0];
    rgb[3 * offset + 1] += splat_scale * splat_rgb[1];
    rgb[3 * offset + 2] += splat_scale * splat_rgb[2];
    rgb[3 * offset] *= scale;
    rgb[3 * offset + 1] *= scale;
    rgb[3 * offset + 2] *= scale;
    ++offset;
  }
  LINFO("Writting image {} with bounds {}", filename, cropped_pixel_bounds);
  //WRITE IMAGE
}
void specula::Film::clear() {
  for (Point2i p : cropped_pixel_bounds) {
    Pixel &pixel = get_pixel(p);
    pixel.splat_xyz[0] = pixel.splat_xyz[1] = pixel.splat_xyz[2] =
        pixel.xyz[0] = pixel.xyz[1] = pixel.xyz[2] = 0;
    pixel.filter_weight_sum = 0;
  }
}
