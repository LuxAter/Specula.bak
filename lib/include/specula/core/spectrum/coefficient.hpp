#ifndef SPECULA_CORE_SPECTRUM_COEFFICIENT_HPP_
#define SPECULA_CORE_SPECTRUM_COEFFICIENT_HPP_

#include "core/geometry/common.hpp"
#include "global/compiler.hpp"
#include "global/declarations.hpp"
#include "specula/global.hpp"

namespace specula {
enum class SpectrumType { REFLECTANCE, ILLUMINANT };
template <std::size_t N> class CoefficientSpectrum {
public:
  typedef std::size_t size_type;
  typedef Float &reference;
  typedef Float *pointer;
  typedef const Float &const_reference;
  typedef const Float *const_pointer;

  CoefficientSpectrum(Float v = 0.0f) {
    for (size_type i = 0; i < N; ++i)
      c[i] = v;
    CHECK(!has_nans());
  }

  SPECULA_CONSTEXPR size_type size() const { return N; }
  SPECULA_CONSTEXPR size_type samples() const { return N; }

  inline bool has_nans() const {
    for (size_type i = 0; i < N; ++i)
      if (std::isnan(c[i]))
        return true;
    return false;
  }

  CoefficientSpectrum &operator+=(const CoefficientSpectrum &s2) {
    CHECK(!s2.has_nans());
    for (size_type i = 0; i < N; ++i)
      c[i] += s2.c[i];
    return *this;
  }
  CoefficientSpectrum &operator-=(const CoefficientSpectrum &s2) {
    CHECK(!s2.has_nans());
    for (size_type i = 0; i < N; ++i)
      c[i] -= s2.c[i];
    return *this;
  }
  CoefficientSpectrum &operator*=(const CoefficientSpectrum &s2) {
    CHECK(!s2.has_nans());
    for (size_type i = 0; i < N; ++i)
      c[i] *= s2.c[i];
    return *this;
  }
  CoefficientSpectrum &operator/=(const CoefficientSpectrum &s2) {
    CHECK(!s2.has_nans());
    for (size_type i = 0; i < N; ++i) {
      CHECK_NE(s2.c[i], 0);
      c[i] /= s2.c[i];
    }
    return *this;
  }
  CoefficientSpectrum operator+(const CoefficientSpectrum &s2) const {
    CHECK(!s2.has_nans());
    CoefficientSpectrum ret = *this;
    for (size_type i = 0; i < N; ++i)
      ret.c[i] += s2.c[i];
    return ret;
  }
  CoefficientSpectrum operator-(const CoefficientSpectrum &s2) const {
    CHECK(!s2.has_nans());
    CoefficientSpectrum ret = *this;
    for (size_type i = 0; i < N; ++i)
      ret.c[i] -= s2.c[i];
    return ret;
  }
  CoefficientSpectrum operator*(const CoefficientSpectrum &s2) const {
    CHECK(!s2.has_nans());
    CoefficientSpectrum ret = *this;
    for (size_type i = 0; i < N; ++i)
      ret.c[i] *= s2.c[i];
    return ret;
  }
  CoefficientSpectrum operator/(const CoefficientSpectrum &s2) const {
    CHECK(!s2.has_nans());
    CoefficientSpectrum ret = *this;
    for (size_type i = 0; i < N; ++i) {
      CHECK_NE(s2.c[i], 0);
      ret.c[i] /= s2.c[i];
    }
    return ret;
  }

  CoefficientSpectrum &operator*=(Float s) {
    for (size_type i = 0; i < N; ++i)
      c[i] *= s;
    CHECK(!has_nans());
    return *this;
  }
  CoefficientSpectrum operator*(Float s) const {
    CoefficientSpectrum ret = *this;
    for (size_type i = 0; i < N; ++i)
      ret.c[i] *= s;
    CHECK(!ret.has_nans());
    return ret;
  }
  inline friend CoefficientSpectrum operator*(Float a,
                                              const CoefficientSpectrum &s) {
    CHECK(!std::isnan(a) && !s.has_nans());
    return s * a;
  }
  CoefficientSpectrum &operator/=(Float s) {
    CHECK_NE(s, 0);
    CHECK(!std::isnan(s));
    for (size_type i = 0; i < N; ++i)
      c[i] *= s;
    CHECK(!has_nans());
    return *this;
  }
  CoefficientSpectrum operator/(Float s) const {
    CHECK_NE(s, 0);
    CHECK(!std::isnan(s));
    CoefficientSpectrum ret = *this;
    for (size_type i = 0; i < N; ++i)
      ret.c[i] *= s;
    CHECK(!ret.has_nans());
    return ret;
  }
  inline friend CoefficientSpectrum operator/(Float a,
                                              const CoefficientSpectrum &s) {
    CHECK_NE(a, 0);
    CHECK(!std::isnan(a) && !s.has_nans());
    return s / a;
  }

  inline bool operator==(const CoefficientSpectrum &sp) const {
    for (size_type i = 0; i < N; ++i)
      if (c[i] != sp.c[i])
        return false;
    return true;
  }
  inline bool operator!=(const CoefficientSpectrum &sp) const {
    for (size_type i = 0; i < N; ++i)
      if (c[i] != sp.c[i])
        return true;
    return false;
  }

  CoefficientSpectrum operator-() const {
    CoefficientSpectrum ret;
    for (size_type i = 0; i < N; ++i)
      ret.c[i] = -c[i];
    return ret;
  }

  reference at(const size_type &i) {
    CHECK(i >= 0 && i <= N);
    return c[i];
  }
  SPECULA_CONSTEXPR const_reference at(const size_type &i) const {
    CHECK(i >= 0 && i <= N);
    return c[i];
  }
  reference operator[](const size_type &i) {
    CHECK(i >= 0 && i <= N);
    return c[i];
  }
  SPECULA_CONSTEXPR const_reference operator[](const size_type &i) const {
    CHECK(i >= 0 && i <= N);
    return c[i];
  }

  inline bool is_black() const {
    for (size_type i = 0; i < N; ++i)
      if (c[i] != 0.0f)
        return false;
    return true;
  }

  inline std::string fmt() const {
    std::string res = "[";
    for (size_type i = 0; i < N; ++i)
      res += (i != N - 1) ? fmt::format("{},", c[i]) : fmt::format("{}]", c[i]);
    return res;
  }

protected:
  Float c[N];
};

template <std::size_t N>
std::ostream &operator<<(std::ostream &out, const CoefficientSpectrum<N> &s) {
  return out << s.fmt();
}

template <std::size_t N>
CoefficientSpectrum<N> sqrt(const CoefficientSpectrum<N> &s) {
  CoefficientSpectrum<N> ret;
  for (typename CoefficientSpectrum<N>::size_type i = 0; i < N; ++i)
    ret[i] = std::sqrt(s[i]);
  CHECK(!ret.has_nans());
  return ret;
}
template <std::size_t N>
CoefficientSpectrum<N> pow(const CoefficientSpectrum<N> &s, Float e) {
  CoefficientSpectrum<N> ret;
  for (typename CoefficientSpectrum<N>::size_type i = 0; i < N; ++i)
    ret[i] = std::pow(s[i], e);
  CHECK(!ret.has_nans());
  return ret;
}
template <std::size_t N>
CoefficientSpectrum<N> exp(const CoefficientSpectrum<N> &s) {
  CoefficientSpectrum<N> ret;
  for (typename CoefficientSpectrum<N>::size_type i = 0; i < N; ++i)
    ret[i] = std::exp(s[i]);
  CHECK(!ret.has_nans());
  return ret;
}
template <std::size_t N>
CoefficientSpectrum<N> clamp(const CoefficientSpectrum<N> &s, Float low = 0,
                             Float high = INFTY) {
  CoefficientSpectrum<N> ret;
  for (typename CoefficientSpectrum<N>::size_type i = 0; i < N; ++i)
    ret[i] = clamp(s[i], low, high);
  CHECK(!ret.has_nans());
  return ret;
}
template <std::size_t N> Float max_component(const CoefficientSpectrum<N> &s) {
  Float m = s[0];
  for (typename CoefficientSpectrum<N>::size_type i = 0; i < N; ++i)
    m = std::max(m, s[i]);
  return m;
}
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_SPECTRUM_COEFFICIENT_HPP_ */
