#ifndef SPECULA_MATRIXNXM_HPP_
#define SPECULA_MATRIXNXM_HPP_

#include <memory>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

#include "../../log.hpp"

#include <iostream>

namespace specula {
template <typename T, std::size_t N, std::size_t M> class MatrixNxM {
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
    iterator(const typename MatrixNxM::size_type &r,
             const typename MatrixNxM::size_type &c,
             MatrixNxM *base) SPECULA_NOEXCEPT : r(r),
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
    typename MatrixNxM::size_type r, c;
    MatrixNxM *base;
  };
  class const_iterator {
    typedef T value_type;
    typedef const T &reference;
    typedef const T *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    const_iterator() SPECULA_NOEXCEPT : r(0), c(0), base(nullptr) {}
    const_iterator(const typename MatrixNxM::size_type &r,
                   const typename MatrixNxM::size_type &c,
                   const MatrixNxM *base) SPECULA_NOEXCEPT : r(r),
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
      if (c == M) {
        c = 0;
        ++r;
      }
      return *this;
    }
    const_iterator operator++(int) SPECULA_NOEXCEPT {
      const_iterator old = *this;
      ++c;
      if (c == M) {
        c = 0;
        ++r;
      }
      return old;
    }
    const_iterator &operator--() SPECULA_NOEXCEPT {
      if (c == 0) {
        --r;
        c = M;
      }
      --c;
      return *this;
    }
    const_iterator operator--(int) SPECULA_NOEXCEPT {
      const_iterator old = *this;
      if (c == 0) {
        --r;
        c = M;
      }
      --c;
      return old;
    }

    reference operator*() const { return base[r][c]; }
    pointer operator->() const { return *(base[r][c]); }
    typename MatrixNxM::size_type r, c;
    const MatrixNxM *base;
  };

  class row_iterator {
    typedef T value_type;
    typedef T *reference;
    typedef T *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    row_iterator() SPECULA_NOEXCEPT : r(0), base(nullptr) {}
    row_iterator(const typename MatrixNxM::size_type &r,
                 MatrixNxM *base) SPECULA_NOEXCEPT : r(r),
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
    typename MatrixNxM::size_type r;
    MatrixNxM *base;
  };
  class const_row_iterator {
    typedef T value_type;
    typedef const T &reference;
    typedef const T *pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    const_row_iterator() SPECULA_NOEXCEPT : r(0), base(nullptr) {}
    const_row_iterator(const typename MatrixNxM::size_type &r,
                       const MatrixNxM *base) SPECULA_NOEXCEPT : r(r),
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
    typename MatrixNxM::size_type r;
    const MatrixNxM *base;
  };

  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<row_iterator> reverse_row_iterator;
  typedef std::reverse_iterator<const_row_iterator> const_reverse_row_iterator;

  MatrixNxM() SPECULA_NOEXCEPT {
    std::fill(&data[0][0], &data[0][0] + this->size(), T());
    for (size_type d = 0; d < std::min(this->rows(), this->columns()); ++d) {
      data[d][d] = T(1);
    }
  }
  MatrixNxM(const T &s) {
    std::fill(&data[0][0], &data[0][0] + this->size(), T());
    for (size_type d = 0; d < std::min(this->rows(), this->columns()); ++d) {
      data[d][d] = s;
    }
  }
  template <typename... Args,
            typename = typename std::enable_if<sizeof...(Args) == N * M>::type>
  MatrixNxM(const Args &... args) SPECULA_NOEXCEPT {
    std::fill(&data[0][0], &data[0][0] + this->size(), T());
    initialize<0>(args...);
  }
  MatrixNxM(const MatrixNxM &m) SPECULA_NOEXCEPT {
    std::copy(&m.data[0][0], &m.data[0][0] + this->size(), &data[0][0]);
  }
  ~MatrixNxM() SPECULA_NOEXCEPT {}

  MatrixNxM &operator=(const MatrixNxM &m) SPECULA_NOEXCEPT {
    std::copy(&m.data[0][0], &m.data[0][0] + this->size(), &data[0][0]);
    return *this;
  }

  bool operator==(const MatrixNxM &m) const SPECULA_NOEXCEPT {
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        if (data[r][c] != m.data[r][c])
          return false;
      }
    }
    return true;
  }
  bool operator!=(const MatrixNxM &m) const SPECULA_NOEXCEPT {
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        if (data[r][c] != m.data[r][c])
          return true;
      }
    }
    return false;
  }

  iterator begin() SPECULA_NOEXCEPT { return iterator(0, 0, this); }
  const_iterator begin() const SPECULA_NOEXCEPT {
    return const_iterator(0, 0, this);
  }
  const_iterator cbegin() const SPECULA_NOEXCEPT {
    return const_iterator(0, 0, this);
  }
  iterator end() SPECULA_NOEXCEPT { return iterator(N, 0, this); }
  const_iterator end() const SPECULA_NOEXCEPT {
    return const_iterator(N, 0, this);
  }
  const_iterator cend() const SPECULA_NOEXCEPT {
    return const_iterator(N, 0, this);
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
    return reverse_iterator(N, 0, this);
  }
  const_reverse_iterator rend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(N, 0, this);
  }
  const_reverse_iterator crend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(N, 0, this);
  }

  reference front() SPECULA_NOEXCEPT { return data[0][0]; }
  const_reference front() const SPECULA_NOEXCEPT { return data[0][0]; }
  reference back() SPECULA_NOEXCEPT { return data[N - 1][M - 1]; }
  const_reference back() const SPECULA_NOEXCEPT { return data[N - 1][M - 1]; }
  pointer operator[](size_type r) { return data[r]; }
  const_pointer operator[](size_type r) const { return data[r]; }
  pointer at(size_type r) {
    if (r < 0 || r >= N)
      throw std::out_of_range(
          "specula::MatrixNxM::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    return data[r];
  }
  const_pointer at(size_type r) const {
    if (r < 0 || r >= N)
      throw std::out_of_range(
          "specula::MatrixNxM::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    return data[r];
  }
  reference at(size_type r, size_type c) {
    if (r < 0 || r >= N)
      throw std::out_of_range(
          "specula::MatrixNxM::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    else if (c < 0 || c >= M) {
      throw std::out_of_range(
          "specula::MatrixNxM::_M_range_check: __c (which is " +
              std::to_string(c)
          << ") >= this->columns() (which is " +
                 std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }
  const_reference at(size_type r, size_type c) const {
    if (r < 0 || r >= N)
      throw std::out_of_range(
          "specula::MatrixNxM::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    else if (c < 0 || c >= M) {
      throw std::out_of_range(
          "specula::MatrixNxM::_M_range_check: __c (which is " +
              std::to_string(c)
          << ") >= this->columns() (which is " +
                 std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }

  void clear() SPECULA_NOEXCEPT {
    std::fill(&data[0][0], &data[0][0] + this->size(), T());
  }

  void swap(MatrixNxM &m) SPECULA_NOEXCEPT { std::swap(data, m.data); }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return N * M; }
  SPECULA_CONSTEXPR size_type rows() const SPECULA_NOEXCEPT { return N; }
  SPECULA_CONSTEXPR size_type columns() const SPECULA_NOEXCEPT { return M; }
  SPECULA_CONSTEXPR size_type max_size() const SPECULA_NOEXCEPT {
    return N * M;
  }
  SPECULA_CONSTEXPR bool empty() const SPECULA_NOEXCEPT { return false; }

  MatrixNxM<T, N, M> operator+(const T &s) const SPECULA_NOEXCEPT {
    MatrixNxM<T, N, M> out;
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        out[r][c] = data[r][c] + s;
      }
    }
    return out;
  }
  MatrixNxM operator+(const MatrixNxM &m) const SPECULA_NOEXCEPT {
    MatrixNxM<T, N, M> out;
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        out[r][c] = data[r][c] + m.data[r][c];
      }
    }
    return out;
  }
  MatrixNxM &operator+=(const T &s) SPECULA_NOEXCEPT {
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        data[r][c] += s;
      }
    }
    return *this;
  }
  MatrixNxM &operator+=(const MatrixNxM &m) SPECULA_NOEXCEPT {
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        data[r][c] += m.data[r][c];
      }
    }
    return *this;
  }
  MatrixNxM operator-(const T &s) const SPECULA_NOEXCEPT {
    MatrixNxM<T, N, M> out;
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        out[r][c] = data[r][c] - s;
      }
    }
    return out;
  }
  MatrixNxM operator-(const MatrixNxM &m) const SPECULA_NOEXCEPT {
    MatrixNxM<T, N, M> out;
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        out[r][c] = data[r][c] - m.data[r][c];
      }
    }
    return out;
  }
  MatrixNxM &operator-=(const T &s) SPECULA_NOEXCEPT {
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        data[r][c] -= s;
      }
    }
    return *this;
  }
  MatrixNxM &operator-=(const MatrixNxM &m) SPECULA_NOEXCEPT {
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        data[r][c] -= m.data[r][c];
      }
    }
    return *this;
  }
  MatrixNxM operator*(const T &s) const SPECULA_NOEXCEPT {
    MatrixNxM<T, N, M> out;
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        out[r][c] = data[r][c] * s;
      }
    }
    return *this;
  }
  template <std::size_t R, std::size_t C,
            typename = typename std::enable_if<M == R>::type>
  MatrixNxM<T, N, C>
  operator*(const MatrixNxM<T, R, C> &m) const SPECULA_NOEXCEPT {
    MatrixNxM<T, N, C> out(T(0));
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < m.columns(); ++c) {
        for (size_type k = 0; k < this->columns(); ++k) {
          out[r][c] += data[r][k] * m.data[k][c];
        }
      }
    }
    return out;
  }
  MatrixNxM &operator*=(const T &s) SPECULA_NOEXCEPT {
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        data[r][c] *= s;
      }
    }
    return *this;
  }
  MatrixNxM operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    MatrixNxM<T, N, M> out;
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        out[r][c] = data[r][c] * inv;
      }
    }
    return out;
  }
  MatrixNxM operator/(const MatrixNxM &m) const SPECULA_NOEXCEPT {
    MatrixNxM<T, N, M> out;
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        out[r][c] = data[r][c] / m.data[r][c];
      }
    }
    return out;
  }
  MatrixNxM &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        data[r][c] *= inv;
      }
    }
    return *this;
  }
  MatrixNxM &operator/=(const MatrixNxM &m) SPECULA_NOEXCEPT {
    for (size_type r = 0; r < this->rows(); ++r) {
      for (size_type c = 0; c < this->columns(); ++c) {
        data[r][c] /= m.data[r][c];
      }
    }
    return *this;
  }

  std::string fmt() const {
    std::string result = "[";
    for (size_type r = 0; r < this->rows(); ++r) {
      result += '[';
      for (size_type c = 0; c < this->columns(); ++c) {
        result += fmt::format("{}", data[r][c]) +
                  ((c == this->columns() - 1) ? ']' : ',');
      }
      result += ((r == this->rows() - 1) ? "]" : ",");
    }
    return result;
  }

  T data[N][M];

private:
  template <std::size_t I>
  typename std::enable_if<(I < N * M)>::type initialize(const T &v) {
    const size_type c = I % M;
    const size_type r = I / M;
    data[r][c] = v;
  }
  template <std::size_t I, typename... Args>
  typename std::enable_if<(I < N * M)>::type initialize(const T &v,
                                                        const Args &... args) {
    const size_type c = I % M;
    const size_type r = I / M;
    data[r][c] = v;
    initialize<I + 1>(args...);
  }
};

template <std::size_t N, std::size_t M>
using MatrixNxMf = MatrixNxM<Float, N, M>;
template <std::size_t N, std::size_t M> using MatrixNxMi = MatrixNxM<Int, N, M>;

template <typename T, std::size_t N, std::size_t M>
std::ostream &operator<<(std::ostream &out, const MatrixNxM<T, N, M> &m) {
  return out << m.fmt();
}
} // namespace specula

#endif // SPECULA_MATRIXNXN_HPP_
