#ifndef SPECULA_CORE_FILTER_HPP_
#define SPECULA_CORE_FILTER_HPP_

#include "specula/core/geometry.hpp"
#include "specula/global.hpp"

namespace specula {
class Filter {
public:
  Filter(const Vector2f &radius)
      : radius(radius), inv_radius(Vector2f(1 / radius.x, 1 / radius.y)) {}
  virtual ~Filter() {}
  virtual Float evaluate(const Point2f &p) const = 0;
  const Vector2f radius, inv_radius;
};
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_FILTER_HPP_ */
