#ifndef SPECULA_DEV_PROGRESS_HPP_
#define SPECULA_DEV_PROGRESS_HPP_

#include "../global.hpp"

#include <atomic>
#include <chrono>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>

namespace specula {

// namespace iter {
// template <typename It>
// class IteratorWrapper
// : public std::iterator<std::forward_iterator_tag,
// typename std::iterator_traits<It>::value_type> {
// public:
// typedef typename std::iterator_traits<It>::value_type value_type;

// IteratorWrapper() : p(nullptr) {}
// explicit IteratorWrapper(It x) : p(x) {}
// explicit IteratorWrapper(const IteratorWrapper &other) : p(other.p) {}

// virtual inline void incr() { ++p; }
// virtual inline void incr() const { ++p; }

// constexpr inline IteratorWrapper &operator++() {
// incr();
// return *this;
// }
// constexpr inline const IteratorWrapper &operator++() const {
// incr();
// return *this;
// }
// constexpr inline IteratorWrapper operator++(int) const {
// IteratorWrapper tmp(*this);
// incr();
// return tmp;
// }

// template <typename OtherIt>
// constexpr inline bool operator==(const IteratorWrapper<OtherIt> &rhs) const {
// return p == rhs.p;
// }
// template <typename OtherIt>
// constexpr inline bool operator!=(const IteratorWrapper<OtherIt> &rhs) const {
// return p != rhs.p;
// }
// template <typename OtherIt>
// constexpr inline std::size_t operator-(const IteratorWrapper<OtherIt> &rhs) {
// return p - rhs.p;
// }

// inline value_type &operator*() { return *p; }
// inline const value_type &operator*() const { return *p; }
// inline value_type &operator->() { return *p; }
// inline const value_type &operator->() const { return *p; }

// inline It &get() { return p; }
// inline const It &get() const { return p; }

// void swap(IteratorWrapper &other) noexcept { std::swap(p, other.p); }

// template <typename = typename std::is_pointer<It>>
// explicit operator bool() const {
// return p != nullptr;
// }

// private:
// mutable It p;
// };

// template <typename T = std::size_t>
// class RangeIterator : public std::iterator<std::forward_iterator_tag, T> {
// public:
// RangeIterator(T total) : current(0), total(total), step(1) {}
// RangeIterator(T start, T total) : current(start), total(total), step(1) {}
// RangeIterator(T start, T total, T step)
// : current(start), total(total), step(step) {}

// T &operator*() { return current; }
// const T &operator*() const { return current; }

// RangeIterator &operator++() {
// current += step;
// return *this;
// }
// RangeIterator operator++(int) const {
// RangeIterator tmp(*this);
// current += step;
// return tmp;
// }
// explicit operator bool() const { return current < total; }
// bool operator!=(const RangeIterator &) const { return current < total; }
// bool operator==(const RangeIterator &) const { return current >= total; }
// T operator-(const RangeIterator &it) const {
// return (it.total - it.current) / it.step;
// }

// private:
// mutable T current;
// T total;
// T step;
// };

// template <typename It> class Reporter : public IteratorWrapper<It> {
// public:
// explicit Reporter(It begin, It end)
// : IteratorWrapper<It>(begin), end_it(end),
// uuid(RandomGenerator::get()->rand<std::size_t>()), n(0),
// total(std::distance(begin, end)), update(1),
// start_tp(std::chrono::system_clock::now()), desc(), unit("it") {}
// explicit Reporter(It begin, std::size_t total)
// : IteratorWrapper<It>(begin), end_it(begin + total),
// uuid(RandomGenerator::get()->rand<std::size_t>()), n(0), total(total),
// update(1), start_tp(std::chrono::system_clock::now()), desc(),
// unit("it") {}
// template <typename Container,
// typename = typename std::enable_if<
// !std::is_same<Container, Reporter>::value>::type>
// Reporter(Container &v)
// : IteratorWrapper<It>(std::begin(v)), end_it(std::end(v)),
// uuid(RandomGenerator::get()->rand<std::size_t>()), n(0),
// total(std::distance(std::begin(v), std::end(v))), update(1),
// start_tp(std::chrono::system_clock::now()), desc(), unit("it") {}

// Reporter &begin() { return *this; }
// const Reporter &begin() const { return *this; }
// Reporter end() const { return Reporter(end_it, end_it); }

// explicit operator It() { return this->get(); }

// explicit inline operator bool() const { return this->get() != end_it; }

// private:
// const It end_it;
// const std::size_t uuid;
// std::atomic<std::size_t> n;
// std::size_t total, update;
// std::chrono::system_clock::time_point start_tp;
// const std::string_view desc, unit;
// };

// template <typename It, typename ReporterType = Reporter<It>>
// constexpr inline ReporterType report(It begin, It end) {
// return ReporterType(begin, end);
// }
// template <typename It, typename ReporterType = Reporter<It>>
// constexpr inline ReporterType report(It begin, std::size_t total) {
// return ReporterType(begin, total);
// }
// template <typename Container,
// typename ReporterType = Reporter<typename Container::iterator>>
// constexpr inline ReporterType report(Container &v) {
// return ReporterType(v);
// }
// template <std::size_t N, typename T, typename ReporterType = Reporter<T *>>
// constexpr inline ReporterType report(T (&arr)[N]) {
// return ReporterType(arr, N);
// }
// template <typename T> constexpr inline Reporter<RangeIterator<T>> range(T n)
// { return Reporter<RangeIterator<T>>(RangeIterator<T>(n),
// RangeIterator<T>(n));
// }
// template <typename T>
// constexpr inline Reporter<RangeIterator<T>> range(T start, T end) {
// return Reporter<RangeIterator<T>>(RangeIterator<T>(start, end),
// RangeIterator<T>(start, end));
// }
// template <typename T>
// constexpr inline Reporter<RangeIterator<T>> range(T start, T end, T step) {
// return Reporter<RangeIterator<T>>(RangeIterator<T>(start, end, step),
// RangeIterator<T>(start, end, step));
// }

// } // namespace iter

extern std::vector<std::function<void(
    const std::size_t &, const std::string_view &, const std::string_view &,
    const std::size_t &, const std::size_t &, const float &)>>
    progress_reporter_default_callbacks;

class ProgressReporter {
public:
  inline ProgressReporter(std::size_t total, std::size_t update = 1)
      : uuid(RandomGenerator::get()->rand<std::size_t>()), n(0), total(total),
        update_interval(update), tp(std::chrono::system_clock::now()), desc(),
        unit("it"), callbacks(progress_reporter_default_callbacks) {
    for (auto &callback : callbacks)
      callback(uuid, desc, unit, n, total, 0.0f);
  }
  inline ProgressReporter(const std::string &desc, std::size_t total,
                          std::size_t update = 1)
      : uuid(RandomGenerator::get()->rand<std::size_t>()), n(0), total(total),
        update_interval(update), tp(std::chrono::system_clock::now()),
        desc(desc), unit("it"), callbacks(progress_reporter_default_callbacks) {
    for (auto &callback : callbacks)
      callback(uuid, desc, unit, n, total, 0.0f);
  }
  inline ProgressReporter(const std::string &desc, const std::string &unit,
                          std::size_t total, std::size_t update = 1)
      : uuid(RandomGenerator::get()->rand<std::size_t>()), n(0), total(total),
        update_interval(update), tp(std::chrono::system_clock::now()),
        desc(desc), unit(unit), callbacks(progress_reporter_default_callbacks) {
    for (auto &callback : callbacks)
      callback(uuid, desc, unit, n, total, 0.0f);
  }
  inline ~ProgressReporter() {
    n = total;
    std::chrono::system_clock::time_point now_tp =
        std::chrono::system_clock::now();
    float elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now_tp - tp)
            .count() /
        1e3f;
    for (auto &callback : callbacks)
      callback(uuid, desc, unit, n, total, elapsed);
  }

  inline void start() {
    n = 0;
    for (auto &callback : callbacks)
      callback(uuid, desc, unit, n, total, 0.0f);
  }
  inline void end() {
    n = total;
    std::chrono::system_clock::time_point now_tp =
        std::chrono::system_clock::now();
    float elapsed =
        std::chrono::duration_cast<std::chrono::milliseconds>(now_tp - tp)
            .count() /
        1e3f;
    for (auto &callback : callbacks)
      callback(uuid, desc, unit, n, total, elapsed);
  }

  inline void update(std::size_t i = 1) {
    n += i;
    if ((n % update_interval) == 0) {
      std::chrono::system_clock::time_point now_tp =
          std::chrono::system_clock::now();
      float elapsed =
          std::chrono::duration_cast<std::chrono::milliseconds>(now_tp - tp)
              .count() /
          1e3f;
      for (auto &callback : callbacks)
        callback(uuid, desc, unit, n, total, elapsed);
    }
  }

  inline void register_callback(
      const std::function<void(const std::size_t &, const std::string_view &,
                               const std::string_view &, const std::size_t &,
                               const std::size_t &, const float &)>
          func) {
    callbacks.push_back(func);
  }

  inline void operator()(std::size_t i = 1) { update(i); }
  inline ProgressReporter &operator++() {
    update(1);
    return *this;
  }
  inline ProgressReporter &operator++(int) {
    update(1);
    return *this;
  }
  inline operator bool() const { return false; }

  inline bool is_done() const { return n == total; }

private:
  const std::size_t uuid;

  std::atomic<std::size_t> n;
  std::size_t total, update_interval;
  std::chrono::system_clock::time_point tp;

  const std::string desc, unit;

  std::vector<std::function<void(const std::size_t &, const std::string_view &,
                                 const std::string_view &, const std::size_t &,
                                 const std::size_t &, const float &)>>
      callbacks;
};

inline void progress_reporter_register_default(
    const std::function<void(const std::size_t &, const std::string_view &,
                             const std::string_view &, const std::size_t &,
                             const std::size_t &, const float &)>
        func) {
  progress_reporter_default_callbacks.push_back(func);
}
} // namespace specula

#endif /* end of include guard: SPECULA_DEV_PROGRESS_HPP_ */
