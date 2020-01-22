#ifndef SPECULA_MATRIX2X2_HPP_
#define SPECULA_MATRIX2X2_HPP_

#include <memory>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

namespace specula {
template <typename T> class Matrix2x2 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  class iterator {
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    iterator() SPECULA_NOEXCEPT : r(0), c(0), base(nullptr) {}
    iterator(const typename Matrix2x2::size_type &r,
             const typename Matrix2x2::size_type &c,
             Matrix2x2 *base) SPECULA_NOEXCEPT : r(r),
                                                 c(c),
                                                 base(base) {}
    iterator(const iterator &it) SPECULA_NOEXCEPT : r(it.r),
                                                    c(it.c),
                                                    base(it.base) {}
    ~iterator() SPECULA_NOEXCEPT {}

    iterator &operator=(const iterator &it) SPECULA_NOEXCEPT {
      r = it.r;
      c = it.c;
      base = it.base;
      return *this;
    }

    bool operator==(const iterator &it) const SPECULA_NOEXCEPT {
      return r == it.r && c == it.c && base == it.base;
    }
    bool operator!=(const iterator &it) const SPECULA_NOEXCEPT {
      return r != it.r || c != it.c || base != it.base;
    }
    iterator &operator++() SPECULA_NOEXCEPT {
      ++c;
      if (c == base->columns()) {
        c = 0;
        ++r;
      }
      return *this;
    }
    iterator operator++(int) SPECULA_NOEXCEPT {
      iterator old = *this;
      ++c;
      if (c == base->columns()) {
        c = 0;
        ++r;
      }
      return old;
    }
    iterator &operator--() SPECULA_NOEXCEPT {
      if (c == 0) {
        --r;
        c = base->columns();
      }
      --c;
      return *this;
    }
    iterator operator--(int) SPECULA_NOEXCEPT {
      iterator old = *this;
      if (c == 0) {
        --r;
        c = base->columns();
      }
      --c;
      return old;
    }

    reference operator*() const { return base[r][c]; }
    pointer operator->() const { return *(base[r][c]); }
    typename Matrix2x2::size_type r, c;
    Matrix2x2 *base;
  };
  class const_iterator {
    typedef T value_type;
    typedef const T &reference;
    typedef const T *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    const_iterator() SPECULA_NOEXCEPT : r(0), c(0), base(nullptr) {}
    const_iterator(const typename Matrix2x2::size_type &r,
                   const typename Matrix2x2::size_type &c,
                   const Matrix2x2 *base) SPECULA_NOEXCEPT : r(r),
                                                             c(c),
                                                             base(base) {}
    const_iterator(const const_iterator &it) SPECULA_NOEXCEPT : r(it.r),
                                                                c(it.c),
                                                                base(it.base) {}
    const_iterator(const iterator &it) SPECULA_NOEXCEPT : r(it.r),
                                                          c(it.c),
                                                          base(it.base) {}
    ~const_iterator() SPECULA_NOEXCEPT {}

    const_iterator &operator=(const const_iterator &it) SPECULA_NOEXCEPT {
      r = it.r;
      c = it.c;
      base = it.base;
      return *this;
    }

    bool operator==(const const_iterator &it) const SPECULA_NOEXCEPT {
      return r == it.r && c == it.c && base == it.base;
    }
    bool operator!=(const const_iterator &it) const SPECULA_NOEXCEPT {
      return r != it.r || c != it.c || base != it.base;
    }
    const_iterator &operator++() SPECULA_NOEXCEPT {
      ++c;
      if (c == 2) {
        c = 0;
        ++r;
      }
      return *this;
    }
    const_iterator operator++(int) SPECULA_NOEXCEPT {
      const_iterator old = *this;
      ++c;
      if (c == 2) {
        c = 0;
        ++r;
      }
      return old;
    }
    const_iterator &operator--() SPECULA_NOEXCEPT {
      if (c == 0) {
        --r;
        c = 2;
      }
      --c;
      return *this;
    }
    const_iterator operator--(int) SPECULA_NOEXCEPT {
      const_iterator old = *this;
      if (c == 0) {
        --r;
        c = 2;
      }
      --c;
      return old;
    }

    reference operator*() const { return base[r][c]; }
    pointer operator->() const { return *(base[r][c]); }
    typename Matrix2x2::size_type r, c;
    const Matrix2x2 *base;
  };

  class row_iterator {
    typedef T value_type;
    typedef T *reference;
    typedef T *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    row_iterator() SPECULA_NOEXCEPT : r(0), base(nullptr) {}
    row_iterator(const typename Matrix2x2::size_type &r,
                 Matrix2x2 *base) SPECULA_NOEXCEPT : r(r),
                                                     base(base) {}
    row_iterator(const iterator &it) SPECULA_NOEXCEPT : r(it.r),
                                                        base(it.base) {}
    ~row_iterator() SPECULA_NOEXCEPT {}

    iterator &operator=(const iterator &it) SPECULA_NOEXCEPT {
      r = it.r;
      base = it.base;
      return *this;
    }

    bool operator==(const row_iterator &it) const SPECULA_NOEXCEPT {
      return r == it.r && base == it.base;
    }
    bool operator!=(const row_iterator &it) const SPECULA_NOEXCEPT {
      return r != it.r || base != it.base;
    }
    row_iterator &operator++() SPECULA_NOEXCEPT {
      ++r;
      return *this;
    }
    row_iterator operator++(int) SPECULA_NOEXCEPT {
      row_iterator old = *this;
      ++r;
      return old;
    }
    row_iterator &operator--() SPECULA_NOEXCEPT {
      --r;
      return *this;
    }
    row_iterator operator--(int) SPECULA_NOEXCEPT {
      row_iterator old = *this;
      --r;
      return old;
    }

    reference operator*() const { return base[r]; }
    pointer operator->() const { return *(base[r]); }
    typename Matrix2x2::size_type r;
    Matrix2x2 *base;
  };
  class const_row_iterator {
    typedef T value_type;
    typedef const T &reference;
    typedef const T *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    const_row_iterator() SPECULA_NOEXCEPT : r(0), base(nullptr) {}
    const_row_iterator(const typename Matrix2x2::size_type &r,
                       const Matrix2x2 *base) SPECULA_NOEXCEPT : r(r),
                                                                 base(base) {}
    const_row_iterator(const const_row_iterator &it) SPECULA_NOEXCEPT
        : r(it.r),
          base(it.base) {}
    const_row_iterator(const row_iterator &it) SPECULA_NOEXCEPT
        : r(it.r),
          base(it.base) {}
    ~const_row_iterator() SPECULA_NOEXCEPT {}

    const_row_iterator &
    operator=(const const_row_iterator &it) SPECULA_NOEXCEPT {
      r = it.r;
      base = it.base;
      return *this;
    }

    bool operator==(const const_row_iterator &it) const SPECULA_NOEXCEPT {
      return r == it.r && base == it.base;
    }
    bool operator!=(const const_row_iterator &it) const SPECULA_NOEXCEPT {
      return r != it.r || base != it.base;
    }
    const_row_iterator &operator++() SPECULA_NOEXCEPT {
      ++r;
      return *this;
    }
    const_row_iterator operator++(int) SPECULA_NOEXCEPT {
      const_row_iterator old = *this;
      ++r;
      return old;
    }
    const_row_iterator &operator--() SPECULA_NOEXCEPT {
      --r;
      return *this;
    }
    const_row_iterator operator--(int) SPECULA_NOEXCEPT {
      const_row_iterator old = *this;
      --r;
      return old;
    }

    reference operator*() const { return base[r]; }
    pointer operator->() const { return *(base[r]); }
    typename Matrix2x2::size_type r;
    const Matrix2x2 *base;
  };

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<row_iterator> reverse_row_iterator;
  typedef std::reverse_iterator<const_row_iterator> const_reverse_row_iterator;

  Matrix2x2() SPECULA_NOEXCEPT {
    T unit = T(1);
    T zero = T();
    data[0][0] = unit;
    data[0][1] = zero;
    data[1][0] = zero;
    data[1][1] = unit;
  }
  Matrix2x2(const T &s) {
    T zero = T();
    data[0][0] = s;
    data[0][1] = zero;
    data[1][0] = zero;
    data[1][1] = s;
  }
  Matrix2x2(const T &m00, const T &m01, const T &m10, const T &m11) {
    data[0][0] = m00;
    data[0][1] = m01;
    data[1][0] = m10;
    data[1][1] = m11;
  }
  Matrix2x2(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    memcpy(data, m.data, 4 * sizeof(T));
  }
  ~Matrix2x2() SPECULA_NOEXCEPT {}

  Matrix2x2 &operator=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    memcpy(data, m.data, 4 * sizeof(T));
    return *this;
  }

  bool operator==(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return data[0][0] == m.data[0][0] && data[0][1] == m.data[0][1] &&
           data[1][0] == m.data[1][0] && data[1][1] == m.data[1][1];
  }
  bool operator!=(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return data[0][0] != m.data[0][0] || data[0][1] != m.data[0][1] ||
           data[1][0] != m.data[1][0] || data[1][1] != m.data[1][1];
  }

  iterator begin() SPECULA_NOEXCEPT { return iterator(0, 0, this); }
  const_iterator begin() const SPECULA_NOEXCEPT {
    return const_iterator(0, 0, this);
  }
  const_iterator cbegin() const SPECULA_NOEXCEPT {
    return const_iterator(0, 0, this);
  }
  iterator end() SPECULA_NOEXCEPT { return iterator(2, 0, this); }
  const_iterator end() const SPECULA_NOEXCEPT {
    return const_iterator(2, 0, this);
  }
  const_iterator cend() const SPECULA_NOEXCEPT {
    return const_iterator(2, 0, this);
  }
  reverse_iterator rbegin() SPECULA_NOEXCEPT {
    return reverse_iterator(0, 0, this);
  }
  const_reverse_iterator rbegin() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(0, 0, this);
  }
  const_reverse_iterator crbegin() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(0, 0, this);
  }
  reverse_iterator rend() SPECULA_NOEXCEPT {
    return reverse_iterator(2, 0, this);
  }
  const_reverse_iterator rend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(2, 0, this);
  }
  const_reverse_iterator crend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(2, 0, this);
  }

  reference front() SPECULA_NOEXCEPT { return data[0][0]; }
  const_reference front() const SPECULA_NOEXCEPT { return data[0][0]; }
  reference back() SPECULA_NOEXCEPT { return data[1][1]; }
  const_reference back() const SPECULA_NOEXCEPT { return data[1][1]; }
  reference operator[](size_type r) { return data[r]; }
  const_reference operator[](size_type r) const { return data[r]; }
  reference at(size_type r) {
    if (r < 0 || r >= 2)
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    return data[r];
  }
  const_reference at(size_type r) const {
    if (r < 0 || r >= 2)
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    return data[r];
  }
  reference at(size_type r, size_type c) {
    if (r < 0 || r >= 2)
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    else if (c < 0 || c >= 2) {
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __c (which is " +
              std::to_string(c)
          << ") >= this->columns() (which is " +
                 std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }
  const_reference at(size_type r, size_type c) const {
    if (r < 0 || r >= 2)
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    else if (c < 0 || c >= 2) {
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __c (which is " +
              std::to_string(c)
          << ") >= this->columns() (which is " +
                 std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }

  void clear() SPECULA_NOEXCEPT {
    T zero = T();
    data[0][0] = zero;
    data[0][1] = zero;
    data[1][0] = zero;
    data[1][1] = zero;
  }

  void swap(Matrix2x2 &m) SPECULA_NOEXCEPT { std::swap(data, m.data); }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 4; }
  SPECULA_CONSTEXPR size_type rows() const SPECULA_NOEXCEPT { return 2; }
  SPECULA_CONSTEXPR size_type columns() const SPECULA_NOEXCEPT { return 2; }
  SPECULA_CONSTEXPR size_type max_size() const SPECULA_NOEXCEPT { return 4; }
  SPECULA_CONSTEXPR bool empty() const SPECULA_NOEXCEPT { return false; }

  Matrix2x2 operator+(const T &s) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] + s, data[0][1] + s, data[1][0] + s,
                     data[1][1] + s);
  }
  Matrix2x2 operator+(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] + m.data[0][0], data[0][1] + m.data[0][1],
                     data[1][0] + m.data[1][0], data[1][1] + m.data[1][1]);
  }
  Matrix2x2 &operator+=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] += s;
    data[0][1] += s;
    data[1][0] += s;
    data[1][1] += s;
    return *this;
  }
  Matrix2x2 &operator+=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    data[0][0] += m.data[0][0];
    data[0][1] += m.data[0][1];
    data[1][0] += m.data[1][0];
    data[1][1] += m.data[1][1];
    return *this;
  }
  Matrix2x2 operator-(const T &s) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] - s, data[0][1] - s, data[1][0] - s,
                     data[1][1] - s);
  }
  Matrix2x2 operator-(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] - m.data[0][0], data[0][1] - m.data[0][1],
                     data[1][0] - m.data[1][0], data[1][1] - m.data[1][1]);
  }
  Matrix2x2 &operator-=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] -= s;
    data[0][1] -= s;
    data[1][0] -= s;
    data[1][1] -= s;
    return *this;
  }
  Matrix2x2 &operator-=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    data[0][0] -= m.data[0][0];
    data[0][1] -= m.data[0][1];
    data[1][0] -= m.data[1][0];
    data[1][1] -= m.data[1][1];
    return *this;
  }
  Matrix2x2 operator*(const T &s) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] * s, data[0][1] * s, data[1][0] * s,
                     data[1][1] * s);
  }
  Matrix2x2 operator*(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return Matrix2x2<T>(data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0],
                        data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1],
                        data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2],
                        data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0],
                        data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1]);
  }
  Matrix2x2 &operator*=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] *= s;
    data[0][1] *= s;
    data[1][0] *= s;
    data[1][1] *= s;
    return *this;
  }
  Matrix2x2 &operator*=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    value_type t0, t1;
    t0 = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0];
    t1 = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1];

    data[0][0] = t0;
    data[0][1] = t1;

    t0 = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0];
    t1 = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1];

    data[1][0] = t0;
    data[1][1] = t1;

    t0 = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0];
    t1 = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1];

    data[2][0] = t0;
    data[2][1] = t1;

    t0 = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0];
    t1 = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1];

    data[2][0] = t0;
    data[2][1] = t1;

    return *this;
  }
  Matrix2x2 operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Matrix2x2(data[0][0] * inv, data[0][1] * inv, data[1][0] * inv,
                     data[1][1] * inv);
  }
  Matrix2x2 operator/(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] / m.data[0][0], data[0][1] / m.data[0][1],
                     data[1][0] / m.data[1][0], data[1][1] / m.data[1][1]);
  }
  Matrix2x2 &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    data[0][0] *= inv;
    data[0][1] *= inv;
    data[1][0] *= inv;
    data[1][1] *= inv;
    return *this;
  }
  Matrix2x2 &operator/=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    data[0][0] /= m.data[0][0];
    data[0][1] /= m.data[0][1];
    data[1][0] /= m.data[1][0];
    data[1][1] /= m.data[1][1];
    return *this;
  }

  std::string fmt() const {
    return fmt::format("[[{},{}],[{},{}]]", data[0][0], data[0][1], data[1][0],
                       data[1][1]);
  }

  T data[2][2];
};

typedef Matrix2x2<Float> Matrix2f;
typedef Matrix2x2<Int> Matrix2i;
typedef Matrix2x2<Float> Matrix2x2f;
typedef Matrix2x2<Int> Matrix2x2i;

template <typename T> using Matrix2 = Matrix2x2<T>;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix2x2<T> &m) {
  return out << m.fmt();
}
} // namespace specula

#endif // SPECULA_MATRIX2X2_HPP_
