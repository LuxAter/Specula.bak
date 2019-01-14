#include "util/timer.hpp"

#include <array>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

#include <sys/ioctl.h>
#include <unistd.h>

#include <iostream>

static unsigned width_ = 0;

static std::chrono::high_resolution_clock::time_point t0_, t1_, t2_, t3_, t4_,
    t5_, t6_, t7_;

void specula::util::timer::Start(uint8_t timer) {
  switch (timer) {
    case 0:
      t0_ = std::chrono::high_resolution_clock::now();
      break;
    case 1:
      t1_ = std::chrono::high_resolution_clock::now();
      break;
    case 2:
      t2_ = std::chrono::high_resolution_clock::now();
      break;
    case 3:
      t3_ = std::chrono::high_resolution_clock::now();
      break;
    case 4:
      t4_ = std::chrono::high_resolution_clock::now();
      break;
    case 5:
      t5_ = std::chrono::high_resolution_clock::now();
      break;
    case 6:
      t6_ = std::chrono::high_resolution_clock::now();
      break;
    case 7:
      t7_ = std::chrono::high_resolution_clock::now();
      break;
  }
}
double specula::util::timer::Stop(uint8_t timer) {
  switch (timer) {
    case 0:
      return std::chrono::duration_cast<std::chrono::duration<double>>(
                 std::chrono::high_resolution_clock::now() - t0_)
          .count();
    case 1:
      return std::chrono::duration_cast<std::chrono::duration<double>>(
                 std::chrono::high_resolution_clock::now() - t1_)
          .count();
    case 2:
      return std::chrono::duration_cast<std::chrono::duration<double>>(
                 std::chrono::high_resolution_clock::now() - t2_)
          .count();
    case 3:
      return std::chrono::duration_cast<std::chrono::duration<double>>(
                 std::chrono::high_resolution_clock::now() - t3_)
          .count();
    case 4:
      return std::chrono::duration_cast<std::chrono::duration<double>>(
                 std::chrono::high_resolution_clock::now() - t4_)
          .count();
    case 5:
      return std::chrono::duration_cast<std::chrono::duration<double>>(
                 std::chrono::high_resolution_clock::now() - t5_)
          .count();
    case 6:
      return std::chrono::duration_cast<std::chrono::duration<double>>(
                 std::chrono::high_resolution_clock::now() - t6_)
          .count();
    case 7:
      return std::chrono::duration_cast<std::chrono::duration<double>>(
                 std::chrono::high_resolution_clock::now() - t7_)
          .count();
  }
  return 0.0;
}

std::array<unsigned, 6> specula::util::timer::SplitTime(double sec) {
  sec *= 1e9;
  std::array<unsigned, 6> repr{{0, 0, 0, 0, 0, 0}};
  repr[0] = std::floor(sec / (3600e9));
  sec -= repr[0] * (3600 * 1e9);
  repr[1] = std::floor(sec / (60e9));
  sec -= repr[1] * (60 * 1e9);
  repr[2] = std::floor(sec / (1e9));
  sec -= repr[2] * (1e9);
  repr[3] = std::floor(sec / (1e6));
  sec -= repr[3] * (1e6);
  repr[4] = std::floor(sec / (1e3));
  sec -= repr[4] * (1e3);
  repr[5] = sec;
  return repr;
}

std::string specula::util::timer::FmtTime(double sec, uint8_t start,
                                          uint8_t stop, bool trim, bool chars) {
  std::array<unsigned, 6> t = SplitTime(sec);
  std::stringstream ss;
  ss << ' ';
  bool active = false;
  if (!chars) {
    ss << std::setfill('0');
  }
  if ((!trim || (t[0] != 0 || active)) && stop >= 0 && start <= 0) {
    ss << std::setw(2) << t[0];
    ss << ((chars) ? "h " : ":");
    active = true;
  }
  if ((!trim || (t[1] != 0 || active)) && stop >= 1 && start <= 1) {
    ss << std::setw(2) << t[1];
    ss << ((chars) ? "m " : ":");
    active = true;
  }
  if ((!trim || (t[2] != 0 || active)) && stop >= 2 && start <= 2) {
    ss << std::setw(2) << t[2];
    ss << ((chars) ? "s " : ":");
    active = true;
  }
  if ((!trim || (t[3] != 0 || active)) && stop >= 3 && start <= 3) {
    ss << std::setw(3) << t[3];
    ss << ((chars) ? "ms " : ":");
    active = true;
  }
  if ((!trim || (t[4] != 0 || active)) && stop >= 4 && start <= 4) {
    ss << std::setw(3) << t[4];
    ss << ((chars) ? "μs " : ":");
    active = true;
  }
  if ((!trim || (t[5] != 0 || active)) && stop >= 5 && start <= 5) {
    ss << std::setw(3) << t[5];
    ss << ((chars) ? "ns " : ":");
  }
  std::string repr = ss.str();
  repr.pop_back();
  return repr;
}

double specula::util::timer::ETC(double avg, const unsigned long& remaining) {
  return avg * remaining;
}
double specula::util::timer::ETT(double avg, const unsigned long& total) {
  return avg * total;
}

std::string specula::util::timer::FmtETC(double avg,
                                         const unsigned long& remaining,
                                         bool up_line) {
  return ((up_line) ? "\033[F\033[2K" : "") +
         FmtTime(avg * remaining, 0, 3, false, false);
}
// std::string specula::util::timer::FmtProc(double avg,
//                                           const unsigned long& remaining,
//                                           const unsigned long& total,
//                                           bool up_line) {
//   return ((up_line) ? "\033[F\033[2K" : "") +
//          FmtTime(avg * remaining, 0, 3, false, false) + " / " +
//          FmtTime(avg * total, 0, 3, false, false) + '\n';
// }

std::string specula::util::timer::FmtProc(double total_time,
                                          const unsigned long& i,
                                          const unsigned long& total, bool bar,
                                          bool perc, bool up_line) {
  if (width_ == 0) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width_ = w.ws_col - 2;
  }
  double avg = total_time / i;
  unsigned long remaining = total - i;
  std::stringstream ss;
  double perc_val = ((100.0 * i) / total) + 1.0;
  ss << std::fixed << std::setprecision(1) << std::setw(5)<< perc_val << '%';
  std::string perc_str = ss.str();
  std::string bar_str = '[' + std::string(std::ceil(width_ * perc_val / 100.0), '#') + std::string(std::max(0.0, std::floor(width_ * (1.0 - perc_val / 100.0))), ' ') + ']';
  return (up_line ? (bar ? "\033[F\033[2K\033[F\033[2K" : "\033[F\033[2K")
                  : "") +
         FmtTime(avg * remaining, 0, 3, false, false) + " / " +
         FmtTime(avg * total, 0, 3, false, false) +
         (perc ? " [" + perc_str + "]" : "") + '\n' + 
         (bar ? bar_str + "\n" : "");
}
