#ifndef SPECULA_CORE_EFLOAT_HPP_
#define SPECULA_CORE_EFLOAT_HPP_

#include "../global.hpp"

namespace specula {
class EFloat {
public:
  EFloat() {}
  EFloat(Float v, Float err = 0.0f);
  EFloat(Float v, long double lD, Float err);

  EFloat operator+(EFloat ef) const;
  inline explicit operator float() const { return v; }
  inline explicit operator double() const { return v; }

  Float get_absolute_error() const;
  Float upper_bound();
  Float lower_bound();
  Float get_relative_error() const;

};
} // namespace specula

#endif // SPECULA_CORE_EFLOAT_HPP_
