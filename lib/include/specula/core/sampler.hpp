#ifndef SPECULA_CORE_SAMPLER_HPP_
#define SPECULA_CORE_SAMPLER_HPP_

#include "specula/global.hpp"

#include "geometry.hpp"
#include "camera.hpp"
#include "rng.hpp"
#include <vector>

namespace specula {
class Sampler {
public:
  Sampler(std::int64_t samples_per_pixel);

  virtual ~Sampler();

  virtual void start_pixel(const Point2i &p);

  virtual Float get1d() = 0;
  virtual Point2f get2d() = 0;
  CameraSample get_camera_sample(const Point2i &raster);
  void request_1d_array(int n);
  void request_2d_array(int n);
  virtual int round_count(int n) const { return n; }
  const Float *get_1d_array(int n);
  const Point2f *get_2d_array(int n);
  virtual bool start_next_sample();
  virtual std::unique_ptr<Sampler> clone(int seed) = 0;
  virtual bool set_sample_number(std::int64_t sample_num);
  std::string state_string() const {
    return fmt::format("({},{}), sample {}", current_pixel.x, current_pixel.y,
                       current_pixel_sample_index);
  }
  std::int64_t current_sample_number() const {
    return current_pixel_sample_index;
  }

  const std::int64_t samples_per_pixel;

protected:
  Point2i current_pixel;
  std::int64_t current_pixel_sample_index;
  std::vector<int> samples_1d_array_sizes, samples_2d_array_sizes;
  std::vector<std::vector<Float>> sample_array_1d;
  std::vector<std::vector<Point2f>> sample_array_2d;

private:
  std::size_t array_1d_offset, array_2d_offset;
};

class PixelSampler : public Sampler {
public:
  PixelSampler(std::int64_t samples_per_pixel, int sampled_dimensions);
  bool start_next_sample();
  bool set_sample_number(std::int64_t);
  Float get1d();
  Point2f get2d();

protected:
  std::vector<std::vector<Float>> samples1d;
  std::vector<std::vector<Point2f>> samples2d;
  int current1d_dimension = 0, current2d_dimension = 0;
  Rng rng;
};

class GlobalSampler : public Sampler {
public:
  GlobalSampler(std::int64_t samples_per_pixel) : Sampler(samples_per_pixel) {}
  bool start_next_sample();
  void start_pixel(const Point2i &p);
  bool set_sample_number(std::int64_t);
  Float get1d();
  Point2f get2d();
  virtual std::int64_t get_index_for_sample(std::int64_t sample_num) const = 0;
  virtual Float sample_dimension(std::int64_t index, int dimension) const = 0;

protected:
  int dimension;
  std::int64_t interval_sample_index;
  static const int array_start_dim = 5;
  int array_end_dim;
};
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_SAMPLER_HPP_ */
