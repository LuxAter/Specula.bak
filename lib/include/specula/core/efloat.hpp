#ifndef SPECULA_CORE_EFLOAT_HPP_
#define SPECULA_CORE_EFLOAT_HPP_

#include "global/constants.hpp"
#include "global/functions.hpp"
namespace specula {
class EFloat {
public:
  EFloat() {}
  EFloat(const EFloat &ef) {
    ef.check();
    v = ef.v;
    low = ef.low;
    high = ef.high;
#ifdef __DEBUG__
    precise = ef.precise;
#endif // __DEBUG__
  }
  EFloat(float v, float err = 0.0f) : v(v) {
    if (err == 0.0f) {
      low = high = v;
    } else {
      low = next_float_down(v - err);
      high = next_float_up(v + err);
    }
#ifdef __DEBUG__
    precise = v;
    check();
#endif // __DEBUG__
  }

  EFloat &operator=(const EFloat &ef) {
    ef.check();
    if (&ef != this) {
      v = ef.v;
      low = ef.low;
      high = ef.high;
#ifdef __DEBUG__
      precise = ef.precise;
#endif // __DEBUG__
    }
    return *this;
  }

#ifdef __DEBUG__
  EFloat(float v, long double lD, float err) : EFloat(v, err) {
    precise = lD;
    check();
  }
#endif // __DEBUG__

  EFloat operator+(EFloat ef) const {
    EFloat r;
    r.v = v + ef.v;
#ifdef __DEBUG__
    r.precise = precise + ef.precise;
#endif // __DEBUG__
    r.low = next_float_down(lower_bound() + ef.lower_bound());
    r.high = next_float_up(upper_bound() + ef.upper_bound());
    r.check();
    return r;
  }
  EFloat operator-(EFloat ef) const {
    EFloat r;
    r.v = v - ef.v;
#ifdef __DEBUG__
    r.precise = precise - ef.precise;
#endif // __DEBUG__
    r.low = next_float_down(lower_bound() - ef.lower_bound());
    r.high = next_float_up(upper_bound() - ef.upper_bound());
    r.check();
    return r;
  }
  EFloat operator*(EFloat ef) const {
    EFloat r;
    r.v = v * ef.v;
#ifdef __DEBUG__
    r.precise = precise * ef.precise;
#endif // __DEBUG__
    Float prod[4] = {
        lower_bound() * ef.lower_bound(), upper_bound() * ef.lower_bound(),
        lower_bound() * ef.upper_bound(), upper_bound() * ef.upper_bound()};
    r.low = next_float_down(
        std::min(std::min(prod[0], prod[1]), std::min(prod[2], prod[3])));
    r.high = next_float_up(
        std::max(std::max(prod[0], prod[1]), std::max(prod[2], prod[3])));
    r.check();
    return r;
  }
  EFloat operator/(EFloat ef) const {
    EFloat r;
    r.v = v / ef.v;
#ifdef __DEBUG__
    r.precise = precise / ef.precise;
#endif // __DEBUG__
    Float div[4] = {
        lower_bound() / ef.lower_bound(), upper_bound() / ef.lower_bound(),
        lower_bound() / ef.upper_bound(), upper_bound() / ef.upper_bound()};
    r.low = next_float_down(
        std::min(std::min(div[0], div[1]), std::min(div[2], div[3])));
    r.high = next_float_up(
        std::max(std::max(div[0], div[1]), std::max(div[2], div[3])));
    r.check();
    return r;
  }

  EFloat operator-() const {
    EFloat r;
    r.v = -v;
#ifdef __DEBUG__
    r.precise = -precise;
#endif // __DEBUG__
    r.low = -high;
    r.high = -low;
    r.check();
    return r;
  }

  inline bool operator==(EFloat fe) const { return v == fe.v; }

  explicit operator float() const { return v; }
  explicit operator double() const { return v; }
  float get_absolute_error() const {
    return next_float_up(std::max(std::abs(high - v), std::abs(v - low)));
  }
  float upper_bound() const { return high; }
  float lower_bound() const { return low; }

#ifdef __DEBUG__
  float get_relative_error() const { return std::abs((precise - v) / precise); }
  long double precise_value() const { return precise; }
#endif // __DEBUG__

  inline void check() const {
    if (!std::isinf(low) && !std::isnan(low) && !std::isinf(high) &&
        !std::isnan(high))
      CHECK_LE(low, high);
#ifdef __DEBUG__
    if (!std::isinf(v) && !std::isnan(v)) {
      CHECK_LE(lower_bound(), precise);
      CHECK_LE(precise, upper_bound());
    }
#endif // __DEBUG__
  }

  inline std::string fmt() const {
#ifdef __DEBUG__
    return fmt::format("({}({}) - [{}, {}])", v, precise, low, high);
#else
    return fmt::format("({} - [{}, {}])", v, low, high);
#endif // __DEBUG__
  }

private:
  float v, low, high;
#ifdef __DEBUG__
  long double precise;
#endif // __DEBUG__

  friend inline EFloat sqrt(EFloat ef);
  friend inline EFloat abs(EFloat ef);
  friend inline bool quadratic(EFloat a, EFloat b, EFloat c, EFloat *t0,
                               EFloat *t1);
};

inline EFloat operator+(float f, EFloat ef) { return EFloat(f) + ef; }
inline EFloat operator-(float f, EFloat ef) { return EFloat(f) - ef; }
inline EFloat operator*(float f, EFloat ef) { return EFloat(f) * ef; }
inline EFloat operator/(float f, EFloat ef) { return EFloat(f) / ef; }

inline EFloat sqrt(EFloat ef) {
  EFloat r;
  r.v = std::sqrt(ef.v);
#ifdef __DEBUG__
  r.precise = std::sqrt(ef.precise);
#endif // __DEBUG__
  r.low = next_float_down(std::sqrt(ef.low));
  r.high = next_float_down(std::sqrt(ef.high));
  r.check();
  return r;
}
inline EFloat abs(EFloat ef) {
  if (ef.low >= 0) {
    return ef;
  } else if (ef.high <= 0) {
    EFloat r;
    r.v = -ef.v;
#ifdef __DEBUG__
    r.precise = -ef.precise;
#endif // __DEBUG__
    r.low = -ef.high;
    r.high = -ef.low;
    r.check();
    return r;
  } else {
    EFloat r;
    r.v = std::abs(ef.v);
#ifdef __DEBUG__
    r.precise = std::abs(ef.precise);
#endif // __DEBUG__
    r.low = 0;
    r.high = std::max(-ef.low, ef.high);
    r.check();
    return r;
  }
}
inline bool quadratic(EFloat a, EFloat b, EFloat c, EFloat *t0, EFloat *t1) {
  double discrim = static_cast<double>(b.v) * static_cast<double>(b.v) -
                   4.0 * static_cast<double>(a.v) * static_cast<double>(c.v);
  if (discrim <= 0.0)
    return false;
  double root_discrim = std::sqrt(discrim);
  EFloat float_root_discrim(root_discrim, MACHINE_EPSILON * root_discrim);
  EFloat q;
  if (static_cast<float>(b) < 0.0)
    q = -0.5 * (b - float_root_discrim);
  else
    q = -0.5 * (b + float_root_discrim);
  *t0 = q / a;
  *t1 = c / q;
  if (static_cast<float>(*t0) > static_cast<float>(*t1))
    std::swap(*t0, *t1);
  return true;
}

inline std::ostream &operator<<(std::ostream &out, const EFloat &v) {
  return out << v.fmt();
}

} // namespace specula

#endif /* end of include guard: SPECULA_CORE_EFLOAT_HPP_ */
