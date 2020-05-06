#ifndef SPECULA_CORE_MIPMAP_HPP_
#define SPECULA_CORE_MIPMAP_HPP_

#include "core/geometry/point.hpp"
#include "core/geometry/vector.hpp"
#include "core/parallel.hpp"
#include "core/texture.hpp"
#include "specula/global.hpp"
#include "specula/global/functions.hpp"

namespace specula {
enum class ImageWrap { REPEAT, BLACK, CLAMP };
struct ResampleWeight {
  int first_texel;
  Float weight[4];
};
template <typename T> class MIPMap {
public:
  MIPMap(const Point2f &resolution, const T *img, bool do_tri = false,
         Float max_ansio = 8.0f, ImageWrap wrap_mode = ImageWrap::REPEAT)
      : do_trilinear(do_tri), max_anisotropy(max_ansio), wrap_mode(wrap_mode),
        resolution(resolution) {
    PROF_FUNC();
    std::unique_ptr<T[]> resampled_image = nullptr;
    if (!is_power_of_2(resolution[0]) || !is_power_of_2(resolution[1])) {
      Point2i res_pow2(round_up_pow2(resolution[0]),
                       round_up_pow2(resolution[1]));
      LINFO("Resampling MIPMap from {} to {}(Ratio={}))", resolution.fmt(),
            res_pow2.fmt(),
            static_cast<Float>(res_pow2.x * res_pow2.y) /
                static_cast<Float>(resolution.x * resolution.y));

      std::unique_ptr<ResampleWeight[]> sweights =
          resample_weights(resolution[0], res_pow2[0]);
      resampled_image.reset(new T[res_pow2[0] * res_pow2[1]]);

      parallel_for(
          [&](int t) {
            for (int s = 0; s < res_pow2[0]; ++s) {
              resampled_image[t * res_pow2[0] + s] = 0.0f;
              for (int j = 0; j < 4; ++j) {
                int origs = sweights[s].first_texel + j;
                if (wrap_mode == ImageWrap::REPEAT) {
                  origs = mod(origs, resolution[0]);
                } else if (wrap_mode == ImageWrap::CLAMP) {
                  origs = clamp(origs, 0, resolution[0] - 1);
                }
                if (origs >= 0 && origs < (int)resolution[0]) {
                  resampled_image[t * res_pow2[0] + s] +=
                      sweights[s].weight[j] * img[t * resolution[0] + origs];
                }
              }
            }
          },
          resolution[1], 16);

      std::unique_ptr<ResampleWeight[]> tweights =
          resample_weights(resolution[1], res_pow2[1]);
      std::vector<T *> resample_bufs;
      int n_threads = max_thread_index();
      for (int i = 0; i < n_threads; ++i) {
        resample_bufs.push_back(new T[res_pow2[1]]);
      }

      parallel_for(
          [&](int s) {
            T *work_data = resample_bufs[thread_index];
            for (int t = 0; t < res_pow2[1]; ++t) {
              work_data[t] = 0.0f;
              for (int j = 0; j < 4; ++j) {
                int offset = tweights[t].first_texel + j;
                if (wrap_mode == ImageWrap::REPEAT) {
                  offset = mod(offset, resolution[1]);
                } else if (wrap_mode == ImageWrap::CLAMP) {
                  offset = clamp(offset, 0, (int)resolution[1] - 1);
                }
                if (offset >= 0 && offset < (int)resolution[1]) {
                  work_data[t] += tweights[t].weight[j] *
                                  resampled_image[offset * res_pow2[0] + s];
                }
              }
            }
            for (int t = 0; t < res_pow2[1]; ++t) {
              resampled_image[t * res_pow2[0] + s] = clamp(work_data[t]);
            }
          },
          res_pow2[0], 32);
      for (auto ptr : resample_bufs)
        delete[] ptr;
      resolution = res_pow2;
    }
    int nlevels = 1 + log2(std::max(resolution[0], resolution[1]));
    pyramid.resize(nlevels);
    pyramid[0].reset(
        new BlockedArray<T>(resolution[0], resolution[1],
                            resampled_image ? resampled_image.get() : img));
    for (int i = 1; i < nlevels; ++i) {
      int sres = std::max(1, pyramid[i - 1]->u_size() / 2);
      int tres = std::max(1, pyramid[i - 1]->v_size() / 2);
      pyramid[i].reset(new BlockedArray<T>(sres, tres));
      Parallelor(
          [&](int t) {
            for (int s = 0; s < sres; ++s) {
              (*pyramid[i])(s, t) =
                  0.25f *
                  (texel(i - 1, 2 * s, 2 * t) + texel(i - 1, 2 * s + 1, 2 * t) +
                   texel(i - 1, 2 * s, 2 * t + 1) +
                   texel(i - 1, 2 * s + 1, 2 * t + 1));
            }
          },
          tres, 16);
    }

    if (weight_lut[0] == 0.0) {
      for (int i = 0; i < weight_lut_size; ++i) {
        float alpha = 2;
        Float r2 = Float(i) / Float(weight_lut_size - 1);
        weight_lut[i] = std::exp(-alpha * r2) - std::exp(-alpha);
      }
    }
  }
  int width() const { return resolution[0]; }
  int height() const { return resolution[1]; }
  int levels() const { return pyramid.size(); }
  const T &texel(int level, int s, int t) const {
    CHECK_LT(level, pyramid.size());
    const BlockedArray<T> &l = *pyramid[level];
    switch (wrap_mode) {
    case ImageWrap::REPEAT:
      s = mod(s, l.u_size());
      t = mod(t, l.v_size());
      break;
    case ImageWrap::CLAMP:
      s = clamp(s, 0, l.u_size() - 1);
      t = clamp(t, 0, l.v_size() - 1);
      break;
    case ImageWrap::BLACK: {
      static const T black = 0.0f;
      if (s < 0 || s >= (int)l.u_size() || t < 0 || t >= (int)l.v_size())
        return black;
      break;
    }
    }
    return l(s, t);
  }
  T lookup(const Point2f &st, Float width = 0.0f) const {
    PROF_FUNC();
    Float level = levels() - 1 + log2(std::max(width, Float(1e-8)));
    if (level < 0)
      return triangle(0, st);
    else if (level >= levels() - 1)
      return texel(levels() - 1, 0, 0);
    else {
      int ilevel = std::floor(level);
      Float delta = level - ilevel;
      return lerp(delta, triangle(ilevel, st), triangle(ilevel + 1, st));
    }
  }
  T lookup(const Point2f *st, Vector2f dstdx, Vector2f dstdy) const {
    if (do_trilinear) {
      Float width = std::max(std::max(std::abs(dstdx[0]), std::abs(dstdx[1])),
                             std::max(std::abs(dstdy[0]), std::abs(dstdy[1])));
      return lookup(st, 2 * width);
    }
    PROF_FUNC();

    if (dstdx.length_squared() < dstdy.length_squared())
      std::swap(dstdx, dstdy);
    Float major_length = dstdx.length();
    Float minor_length = dstdy.length();

    if (minor_length * max_anisotropy < major_length && minor_length > 0) {
      Float scale = major_length / (minor_length * max_anisotropy);
      dstdy *= scale;
      minor_length *= scale;
    }
    if (minor_length == 0)
      return triangle(0, st);

    Float lod = std::max(Float(0), levels() - Float(1) + log2(minor_length));
    int ilod = std::floor(lod);
    return lerp(lod - ilod, ewa(ilod, st, dstdx, dstdy),
                ewa(ilod + 1, st, dstdx, dstdy));
  }

private:
  std::unique_ptr<ResampleWeight[]> resample_weights(int old_res, int new_res) {
    CHECK_GE(new_res, old_res);
    std::unique_ptr<ResampleWeight[]> wt(new ResampleWeight[new_res]);
    Float filter_width = 2.0f;
    for (int i = 0; i < new_res; ++i) {
      Float center = (i + 0.5f) * old_res / new_res;
      wt[i].first_texel = std::floor((center - filter_width) + 0.5f);
      for (int j = 0; j < 4; ++j) {
        Float pos = wt[i].first_texel + j + 0.5f;
        wt[i].weight[j] = lanczos((pos - center) / filter_width);
      }
      Float inv_sum_wts = 1 / (wt[i].weight[0] + wt[i].weight[1] +
                               wt[i].weight[2] + wt[i].weight[3]);
      for (int j = 0; j < 4; ++j) {
        wt[i].weight[j] *= inv_sum_wts;
      }
    }
    return wt;
  }
  Float clamp(Float v) { return clamp(v, 0.0f, INFTY); }
  RGBSpectrum clamp(const RGBSpectrum &v) { return clamp(v, 0.0f, INFTY); }
  SampledSpectrum clamp(const SampledSpectrum &v) {
    return clamp(v, 0.0f, INFTY);
  }
  T triangle(int level, const Point2f &st) const {
    level = clamp(level, 0, levels() - 1);
    Float s = st[0] * pyramid[level]->u_size() - 0.5f;
    Float t = st[1] * pyramid[level]->v_size() - 0.5f;
    int s0 = std::floor(s), t0 = std::floor(t);
    Float ds = s - s0, dt = t - t0;
    return (1 - ds) * (1 - dt) * texel(level, s0, t0) +
           (1 - ds) * dt * texel(level, s0, t0 + 1) +
           ds * (1 - dt) * texel(level, s0 + 1, t0) +
           ds * dt * texel(level, s0 + 1, t0 + 1);
  }
  T ewa(int level, Point2f st, Vector2f dst0, Vector2f dst1) const {
    if (level >= levels())
      return texel(levels() - 1, 0, 0);
    st[0] = st[0] * pyramid[level]->u_size() - 0.5f;
    st[1] = st[1] * pyramid[level]->v_size() - 0.5f;
    dst0[0] *= pyramid[level]->u_size();
    dst0[1] *= pyramid[level]->v_size();
    dst1[0] *= pyramid[level]->u_size();
    dst1[1] *= pyramid[level]->v_size();

    Float a = dst0[1] * dst0[1] + dst1[1] * dst1[1] + 1;
    Float b = -2 * (dst0[0] * dst0[1] + dst1[0] * dst1[1]);
    Float c = dst0[0] * dst0[0] + dst1[0] * dst1[0] + 1;
    Float invf = 1 / (a * c - b * b * 0.25f);
    a *= invf;
    b *= invf;
    c *= invf;

    Float det = -b * b + 4 * a * c;
    Float inv_det = 1 / det;
    Float usqrt = std::sqrt(det * c), vsqrt = std::sqrt(a * det);
    int s0 = std::ceil(st[0] - 2 * inv_det * usqrt);
    int s1 = std::floor(st[0] + 2 * inv_det * usqrt);
    int t0 = std::ceil(st[1] - 2 * inv_det * vsqrt);
    int t1 = std::floor(st[1] + 2 * inv_det * vsqrt);

    T sum(0.0f);
    Float sum_wts = 0;
    for (int it = t0; it < t1; ++it) {
      Float tt = it - st[1];
      for (int is = s0; is <= s1; ++is) {
        Float ss = is - st[0];
        Float r2 = a * ss * ss + b * ss * tt + c * tt * tt;
        if (r2 < 1) {
          int index =
              std::min((int)(r2 * weight_lut_size), weight_lut_size - 1);
          Float weight = weight_lut[index];
          sum += texel(level, is, it) * weight;
          sum_wts += weight;
        }
      }
    }
    return sum / sum_wts;
  }

  const bool do_trilinear;
  const Float max_anisotropy;
  const ImageWrap wrap_mode;
  Point2i resolution;
  std::vector<std::unique_ptr<BlockedArray<T>>> pyramid;
  static SPECULA_CONSTEXPR int weight_lut_size = 128;
  static Float weight_lut[weight_lut_size];
};

template <typename T> Float MIPMap<T>::weight_lut[weight_lut_size];
} // namespace specula

#endif // SPECULA_CORE_MIPMAP_HPP_
