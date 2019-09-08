#ifndef SPECULA_TERMINAL_PROGRESS_BAR_HPP_
#define SPECULA_TERMINAL_PROGRESS_BAR_HPP_

#include <chrono>
#include <cstdlib>
#include <string>

namespace specula {
namespace terminal {
class ProgressBar {
public:
  enum Components {
    TIME_ELAPSED = (1 << 0),
    TIME_REMAINING = (1 << 1),
    CURRENT_PROGRESS = (1 << 2),
    CURRENT_PERCENTAGE = (1 << 3),
    PROGRESS_BAR = (1 << 4),
    FIRST_ROW = (1 << 0) | (1 << 1),
    SECOND_ROW = (1 << 2) | (1 << 3) | (1 << 4),
  };
  ProgressBar(const std::string &title, const std::size_t &total,
              const std::uint32_t flags = TIME_ELAPSED | TIME_REMAINING |
                                          CURRENT_PROGRESS |
                                          CURRENT_PERCENTAGE | PROGRESS_BAR);
  ProgressBar(const std::size_t &total,
              const std::uint32_t flags = TIME_ELAPSED | TIME_REMAINING |
                                          CURRENT_PROGRESS |
                                          CURRENT_PERCENTAGE | PROGRESS_BAR);
  void operator()();

  bool file_pipe = false;

private:
  void print_first();
  void print_second();

  std::uint32_t flags_;
  std::string title_;
  std::chrono::high_resolution_clock::time_point start_;
  double total_time_;
  std::size_t current_count_, total_count_;
  std::size_t terminal_width_;
};
} // namespace terminal
} // namespace specula

#endif // SPECULA_TERMINAL_PROGRESS_BAR_HPP_
