#include "specula/cli/progress_bar.hpp"

#include <sys/ioctl.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <string>

specula::terminal::ProgressBar::ProgressBar(const std::string &title,
                                            const std::size_t &total,
                                            const std::uint32_t flags)
    : flags_(flags), title_(title),
      start_(std::chrono::high_resolution_clock::now()), total_time_(0.0),
      current_count_(0), total_count_(total) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  terminal_width_ = std::min(static_cast<int>(w.ws_col), 1000);
}

specula::terminal::ProgressBar::ProgressBar(const std::size_t &total,
                                            const std::uint32_t flags)
    : flags_(flags), title_(),
      start_(std::chrono::high_resolution_clock::now()), total_time_(0.0),
      current_count_(0), total_count_(total) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  terminal_width_ = std::min(static_cast<int>(w.ws_col), 1000);
}

void specula::terminal::ProgressBar::operator()() {
  current_count_++;
  double delta = std::chrono::duration_cast<std::chrono::nanoseconds>(
                     std::chrono::high_resolution_clock::now() - start_)
                     .count() /
                 1e9;
  total_time_ += delta;
  if (current_count_ != 1 && !file_pipe) {
    std::printf("\033[A\033[2K");
    if ((flags_ & PROGRESS_BAR) == PROGRESS_BAR)
      std::printf("\033[A\033[2K");
  }
  if (title_.size() != 0 || (flags_ & TIME_ELAPSED) == TIME_ELAPSED ||
      (flags_ & TIME_REMAINING) == TIME_REMAINING)
    print_first();
  if ((flags_ & CURRENT_PROGRESS) == CURRENT_PROGRESS ||
      (flags_ & CURRENT_PERCENTAGE) == CURRENT_PERCENTAGE ||
      (flags_ & PROGRESS_BAR) == PROGRESS_BAR)
    print_second();
  std::printf("\n");
  start_ = std::chrono::high_resolution_clock::now();
}

void specula::terminal::ProgressBar::print_first() {
  std::printf("  ");
  if (title_.size() != 0)
    std::printf("%s  ", title_.c_str());
  if ((flags_ & TIME_REMAINING) == TIME_REMAINING) {
    double remaining =
        (total_time_ / current_count_) * (total_count_ - current_count_);
    unsigned long hour_count = static_cast<unsigned long>(remaining) / 3600;
    unsigned long minute_count =
        (static_cast<unsigned long>(remaining) % 3600) / 60;
    unsigned long second_count = (static_cast<unsigned long>(remaining) % 60);
    std::printf("%2lu:%02lu:%02lu", hour_count, minute_count, second_count);
  }
  if ((flags_ & TIME_ELAPSED) == TIME_ELAPSED) {
    unsigned long hour_count = static_cast<unsigned long>(total_time_) / 3600;
    unsigned long minute_count =
        (static_cast<unsigned long>(total_time_) % 3600) / 60;
    unsigned long second_count = (static_cast<unsigned long>(total_time_) % 60);
    std::printf("[%2lu:%02lu:%02lu]", hour_count, minute_count, second_count);
  }
}
void specula::terminal::ProgressBar::print_second() {
  bool progress = (flags_ & CURRENT_PROGRESS) == CURRENT_PROGRESS;
  bool percentage = (flags_ & CURRENT_PERCENTAGE) == CURRENT_PERCENTAGE;
  std::printf("\n");
  if (percentage)
    std::printf(" %3lu%% ", 100 * current_count_ / total_count_);
  if (progress) {
    int progress_width = std::to_string(total_count_).size();
    std::printf("(%*lu/%*lu)", progress_width, current_count_, progress_width,
                total_count_);
  }
  if ((flags_ & PROGRESS_BAR) == PROGRESS_BAR) {
    int bar_width = static_cast<int>(
        terminal_width_ - 2 - (6 * percentage) -
        (progress * (2 * std::to_string(total_count_).size() + 3)));
    std::string bar(
        static_cast<std::size_t>(
            bar_width * (current_count_ / static_cast<float>(total_count_))),
        '#');
    std::printf("[%-*s]", bar_width, bar.c_str());
  }
}
