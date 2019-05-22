#include "time.hpp"

#include <chrono>

#include <iostream>

namespace specula::time {
std::chrono::time_point<std::chrono::high_resolution_clock> timers_[8] = {
    std::chrono::time_point<std::chrono::high_resolution_clock>(),
    std::chrono::time_point<std::chrono::high_resolution_clock>(),
    std::chrono::time_point<std::chrono::high_resolution_clock>(),
    std::chrono::time_point<std::chrono::high_resolution_clock>(),
    std::chrono::time_point<std::chrono::high_resolution_clock>(),
    std::chrono::time_point<std::chrono::high_resolution_clock>(),
    std::chrono::time_point<std::chrono::high_resolution_clock>(),
    std::chrono::time_point<std::chrono::high_resolution_clock>()};
}  // namespace specula::time

std::chrono::time_point<std::chrono::high_resolution_clock>
specula::time::start() {
  return std::chrono::high_resolution_clock::now();
}
double specula::time::stop(
    const std::chrono::time_point<std::chrono::high_resolution_clock>&
        start_time_point) {
  return std::chrono::duration<double>(
             std::chrono::high_resolution_clock::now() - start_time_point)
      .count();
}

void specula::time::start(const short unsigned& id) {
  timers_[id] = std::chrono::high_resolution_clock::now();
}

double specula::time::stop(const short unsigned& id) {
  return std::chrono::duration<double>(
             std::chrono::high_resolution_clock::now() - timers_[id])
      .count();
}
