#ifndef SPECULA_MATH_SPLINE_HPP_
#define SPECULA_MATH_SPLINE_HPP_

#include <vector>

#include "vector.hpp"

namespace specula {
namespace math {
  class Spline {
   public:
    enum InterpolationMethod { LINEAR_INTERPOLATION, CUBIC_INTERPOLATION };
    Spline()
        : method_(LINEAR_INTERPOLATION), scale_factor_(1.0), loop_(false) {}
    Spline(const InterpolationMethod& method, const double& scale = 1.0)
        : method_(method), scale_factor_(scale), loop_(false) {}

    void ToggleLoop() { loop_ = !loop_; }

    std::size_t Frames() const {
      return (loop_ ? points_.size() : points_.size() - 1) * scale_factor_;
    }
    std::size_t Offset(std::size_t n) const { return n * scale_factor_; }

    math::vec3<double> operator()(const double& t) {
      double it;
      double mu = std::modf(t / scale_factor_, &it);
      std::size_t i = static_cast<std::size_t>(it);
      math::vec3<double> pos;
      if (!loop_ && i >= points_.size() - 1) {
        return points_.size() - 1;
      }else if(loop_){
        i = i % points_.size();
      }
      switch (method_) {
        case LINEAR_INTERPOLATION: {
          if (loop_) {
            pos =
                points_[i] * (1 - mu) + points_[(i + 1) % points_.size()] * mu;
          } else {
            pos = points_[i] * (1 - mu) +
                  points_[(i + 1 >= points_.size()) ? points_.size() - 1
                                                    : i + 1] *
                      mu;
          }
          break;
        }
        case CUBIC_INTERPOLATION: {
          std::size_t y0, y1, y2, y3;
          if (loop_) {
            y0 = (i == 0) ? points_.size() - 1 : i - 1;
            y1 = i;
            y2 = (i + 1) % points_.size();
            y3 = (i + 2) % points_.size();
          } else {
            y0 = (i == 0) ? i : i - 1;
            y1 = i;
            y2 = (i + 1 >= points_.size()) ? points_.size() - 1 : i + 1;
            y3 = (i + 2 >= points_.size()) ? points_.size() - 1 : i + 2;
          }
          double mu2 = mu * mu;
          math::vec3<double> a0 =
              points_[y3] - points_[y2] - points_[y0] + points_[y1];
          math::vec3<double> a1 = points_[y0] - points_[y1] - a0;
          math::vec3<double> a2 = points_[y2] - points_[y0];
          math::vec3<double> a3 = points_[y1];
          pos = {a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3};
          break;
        }
      }
      return pos;
    }

    inline void prepend(const math::vec3<double>& p) {
      points_.insert(points_.begin(), p);
    }
    inline void append(const math::vec3<double>& p) { points_.push_back(p); }
    inline void insert(const std::size_t i, const math::vec3<double>& p) {
      points_.insert(points_.begin() + i, p);
    }

    inline void pop_front() { points_.erase(points_.begin()); }
    inline void pop_back() { points_.pop_back(); }
    inline void erase(const std::size_t& i) {
      points_.erase(points_.begin() + i);
    }

   private:
    InterpolationMethod method_;
    double scale_factor_;
    bool loop_;
    std::vector<math::vec3<double>> points_;
  };
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_SPLINE_HPP_
