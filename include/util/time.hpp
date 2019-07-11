#ifndef SPECULA_UTIL_TIME_HPP_
#define SPECULA_UTIL_TIME_HPP_

#include <chrono>
#include <thread>

namespace specula {
namespace time {
typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;
typedef std::chrono::duration<double> duration;
typedef std::chrono::seconds seconds;
typedef std::chrono::milliseconds milliseconds;
typedef std::chrono::microseconds microseconds;
typedef std::chrono::nanoseconds nanoseconds;

constexpr auto now = std::chrono::high_resolution_clock::now;

template <class Rep, class Period>
inline constexpr void
sleep(const std::chrono::duration<Rep, Period> &sleep_duration) {
  std::this_thread::sleep_for(sleep_duration);
}
inline void sleep(const double &sleep_duration) {
  std::this_thread::sleep_for(std::chrono::duration<double>(sleep_duration));
}
} // namespace time
} // namespace specula

#endif // SPECULA_UTIL_TIME_HPP_
