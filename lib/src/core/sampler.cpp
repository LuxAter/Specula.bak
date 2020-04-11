#include "specula/core/sampler.hpp"
#include "global/declarations.hpp"

specula::Sampler::Sampler(std::int64_t samples_per_pixel)
    : samples_per_pixel(samples_per_pixel) {}
specula::Sampler::~Sampler() {}
specula::CameraSample
specula::Sampler::get_camera_sample(const Point2i &raster) {
  CameraSample cs;
  cs.film = static_cast<Point2f>(raster) + get2d();
  cs.time = get1d();
  cs.lens = get2d();
  return cs;
}
void specula::Sampler::start_pixel(const Point2i &p) {
  current_pixel = p;
  current_pixel_sample_index = 0;
  array_1d_offset = array_2d_offset = 0;
}
bool specula::Sampler::start_next_sample() {
  array_1d_offset = array_2d_offset = 0;
  return ++current_pixel_sample_index < samples_per_pixel;
}

bool specula::Sampler::set_sample_number(std::int64_t sample_num) {
  array_1d_offset = array_2d_offset = 0;
  current_pixel_sample_index = sample_num;
  return current_pixel_sample_index < samples_per_pixel;
}

void specula::Sampler::request_1d_array(int n) {
  CHECK_EQ(round_count(n), n);
  samples_1d_array_sizes.push_back(n);
  sample_array_1d.push_back((std::vector<Float>(n * samples_per_pixel)));
}
void specula::Sampler::request_2d_array(int n) {
  CHECK_EQ(round_count(n), n);
  samples_2d_array_sizes.push_back(n);
  sample_array_2d.push_back((std::vector<Point2f>(n * samples_per_pixel)));
}

const specula::Float *specula::Sampler::get_1d_array(int n) {
  if (array_1d_offset == sample_array_1d.size())
    return nullptr;
  CHECK_EQ(samples_1d_array_sizes[array_1d_offset], n);
  CHECK_LT(current_pixel_sample_index, samples_per_pixel);
  return &sample_array_1d[array_1d_offset++][current_pixel_sample_index * n];
}
const specula::Point2f *specula::Sampler::get_2d_array(int n) {
  if (array_2d_offset == sample_array_2d.size())
    return nullptr;
  CHECK_EQ(samples_2d_array_sizes[array_2d_offset], n);
  CHECK_LT(current_pixel_sample_index, samples_per_pixel);
  return &sample_array_2d[array_2d_offset++][current_pixel_sample_index * n];
}

specula::PixelSampler::PixelSampler(std::int64_t samples_per_pixel,
                                    int sampled_dimensions)
    : Sampler(samples_per_pixel) {
  for (int i = 0; i < sampled_dimensions; ++i) {
    samples1d.push_back(std::vector<Float>(samples_per_pixel));
    samples2d.push_back(std::vector<Point2f>(samples_per_pixel));
  }
}

bool specula::PixelSampler::start_next_sample() {
  current1d_dimension = current2d_dimension = 0;
  return Sampler::start_next_sample();
}
bool specula::PixelSampler::set_sample_number(std::int64_t sample_num) {
  current1d_dimension = current2d_dimension = 0;
  return Sampler::set_sample_number(sample_num);
}
specula::Float specula::PixelSampler::get1d() {
  PROF_FUNC();
  CHECK_LT(current_pixel_sample_index, samples_per_pixel);
  if (current1d_dimension < samples1d.size())
    return samples1d[current1d_dimension++][current_pixel_sample_index];
  else
    return rng.uniform_float();
}
specula::Point2f specula::PixelSampler::get2d() {
  PROF_FUNC();
  CHECK_LT(current_pixel_sample_index, samples_per_pixel);
  if (current2d_dimension < samples2d.size())
    return samples2d[current2d_dimension++][current_pixel_sample_index];
  else
    return Point2f(rng.uniform_float(), rng.uniform_float());
}

void specula::GlobalSampler::start_pixel(const Point2i &p) {
  PROF_FUNC();
  Sampler::start_pixel(p);
  dimension = 0;
  interval_sample_index = get_index_for_sample(0);
  array_end_dim =
      array_start_dim + sample_array_1d.size() + 2 * sample_array_2d.size();

  for (std::size_t i = 0; i < samples_1d_array_sizes.size(); ++i) {
    int n_samples = samples_1d_array_sizes[i] * samples_per_pixel;
    for (int j = 0; j < n_samples; ++j) {
      std::int64_t index = get_index_for_sample(j);
      sample_array_1d[i][j] = sample_dimension(index, array_start_dim + i);
    }
  }

  int dim = array_start_dim + samples_1d_array_sizes.size();
  for (std::size_t i = 0; i < samples_2d_array_sizes.size(); ++i) {
    int n_samples = samples_2d_array_sizes[i] * samples_per_pixel;
    for (int j = 0; j < n_samples; ++j) {
      std::int64_t index = get_index_for_sample(j);
      sample_array_2d[i][j].x = sample_dimension(index, dim);
      sample_array_2d[i][j].y = sample_dimension(index, dim + 1);
    }
  }
  CHECK_EQ(array_end_dim, dim);
}
bool specula::GlobalSampler::start_next_sample() {
  dimension = 0;
  interval_sample_index = get_index_for_sample(current_pixel_sample_index + 1);
  return Sampler::start_next_sample();
}
bool specula::GlobalSampler::set_sample_number(std::int64_t sample_num) {
  dimension = 0;
  interval_sample_index = get_index_for_sample(sample_num);
  return Sampler::set_sample_number(sample_num);
}
specula::Float specula::GlobalSampler::get1d() {
  PROF_FUNC();
  if (dimension >= array_start_dim && dimension < array_end_dim)
    dimension = array_end_dim;
  return sample_dimension(interval_sample_index, dimension++);
}
specula::Point2f specula::GlobalSampler::get2d() {
  PROF_FUNC();
  if (dimension + 1 >= array_start_dim && dimension < array_end_dim)
    dimension = array_end_dim;
  Point2f p(sample_dimension(interval_sample_index, dimension),
            sample_dimension(interval_sample_index, dimension + 1));
  dimension += 2;
  return p;
}
