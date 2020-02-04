#ifndef SPECULA_DEV_TQDM_HPP_
#define SPECULA_DEV_TQDM_HPP_

#include <chrono>
#include <mutex>
#include <string>
#include <thread>

#include "../extern/optional.hpp"
#include "../extern/variant.hpp"

namespace specula {
template <typename T = std::size_t> class ProgressBar {
public:
  enum Color {
    BOLD,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    DEFAULT
  };
  static std::string format_sizeof(const float& number,
                                   const std::string& suffix = "",
                                   const float& divisor = 1000) {
    float num = number;
    for (auto&& unit : {' ', 'k', 'M', 'G', 'T', 'P', 'E', 'Z'}) {
      if (std::abs(num) < 999.5) {
        if (std::abs(num) < 99.95) {
          if (std::abs(num) < 9.995) {
            return fmt::format("{0:1.2f}", num) + unit + suffix;
          }
          return fmt::format("{0:2.1f}", num) + unit + suffix;
        }
        return fmt::format("{0:3.0f}", num) + unit + suffix;
      }
      num /= divisor;
    }
    return fmt::format("{0:3.1}Y", num) + suffix;
  }
  static std::string format_interval(const std::size_t& t) {
    auto mins_sec = std::div(t, 60);
    auto hour_min = std::div(mins_sec.quot, 60);
    if (hour_min.quot != 0) {
      return fmt::format("{0:d}:{1:02d}:{2:02d}", hour_min.quot, hour_min.rem,
                         mins_sec.rem);
    } else {
      return fmt::format("{0:02d}:{1:02d}", hour_min.rem, mins_sec.rem);
    }
  }
  template <typename U> static std::string format_num(const U& num) {
    std::string f = fmt::format("{0:.3g}", num);
    if (f.find("+0") != std::string::npos) {
      f.replace(f.find("+0"), 2, "+");
    }
    if (f.find("-0") != std::string::npos) {
      f.replace(f.find("-0"), 2, "-");
    }
    std::string n = fmt::format("{}", num);
    return (f.size() < n.size()) ? f : n;
  }

  static std::string
  format_bar(const float& frac, const std::size_t& default_len = 25,
             const char& begin_ch = '[', const char& fill_ch = '#',
             const char& front_ch = '>', const char& rem_ch = ' ',
             const char& end_ch = ']') {
    std::size_t bar_length = std::floor(frac * default_len);
    std::string bar(bar_length, fill_ch);
    if (bar_length < default_len) {
      return begin_ch + bar + front_ch +
             std::string(default_len - bar_length - 1, rem_ch) + end_ch;
    } else {
      return begin_ch + bar + end_ch;
    }
  }
  static std::string format_color(const Color& color) {
    switch (color) {
    case BOLD:
      return "\033[0;1m";
    case BLACK:
      return "\033[0;1;30m";
    case RED:
      return "\033[0;1;31m";
    case GREEN:
      return "\033[0;1;32m";
    case YELLOW:
      return "\033[0;1;33m";
    case BLUE:
      return "\033[0;1;34m";
    case MAGENTA:
      return "\033[0;1;35m";
    case CYAN:
      return "\033[0;1;36m";
    case WHITE:
      return "\033[0;1;37m";
    case DEFAULT:
    default:
      return "\033[0m";
    }
  }

  template <typename U>
  static std::string
  format_meter(const std::string& bar_format, const U& n, const U& total,
               const float& elapsed, const std::string unit = "it",
               const char& bb = '[', const char& bf = '#', const char& bc = '>',
               const char& br = ' ', const char& be = ']',
               bool unit_scale = false) {
    std::string elapsed_fmt = format_interval(elapsed);
    float rate = n / elapsed;
    float inv_rate = 1 / rate;
    std::string rate_noinv_fmt =
        (unit_scale ? format_sizeof(rate) : fmt::format("{:5.2f}", rate)) +
        unit + "/s";
    std::string rate_inv_fmt = (unit_scale ? format_sizeof(inv_rate)
                                           : fmt::format("{:5.2f}", inv_rate)) +
                               "s/" + unit;
    std::string rate_fmt = inv_rate > 1 ? rate_inv_fmt : rate_noinv_fmt;
    std::string n_fmt = unit_scale ? format_sizeof(n) : fmt::format("{}", n);
    std::string total_fmt =
        unit_scale ? format_sizeof(total) : fmt::format("{}", total);
    float remaining = (total - n) / rate;
    std::string remaining_fmt = format_interval(remaining);

    float frac = n / static_cast<float>(total);
    float percentage = frac * 100;
    std::size_t bar_pos = bar_format.find("{bar");
    std::string res = bar_format;
    if (bar_pos != std::string::npos) {
      std::size_t bar_width = 25;
      std::size_t bar_spec_width = 5;
      if (bar_format[bar_pos + 4] == ':') {
        std::string bar_width_str = "";
        std::size_t i = 5;
        while (bar_pos + i < bar_format.size() &&
               bar_format[bar_pos + i] != '}') {
          bar_width_str += bar_format[bar_pos + i];
          bar_spec_width++;
          ++i;
        }
        bar_spec_width++;
        bar_width = std::stoi(bar_width_str.c_str());
      }
      std::string bar = format_bar(frac, bar_width, bb, bf, bc, br, be);
      res.replace(bar_pos, bar_spec_width, bar);
    }
    return fmt::format(
        res, fmt::arg("percentage", percentage), fmt::arg("n", n_fmt),
        fmt::arg("total", total_fmt), fmt::arg("elapsed", elapsed_fmt),
        fmt::arg("remaining", remaining_fmt), fmt::arg("rate", rate_fmt));
  }

  ProgressBar(const std::string format =
                  "{percentage:3.0f}% {bar:40} {n}/{total} "
                  "[{elapsed}<{remaining}, {rate}]{default}",
              const T& total = T(100), const T& step = T(1))
      : format(format), n(0), total(total), step(step),
        tp(std::chrono::high_resolution_clock::now()) {}
  ProgressBar(const T& total, const T& step = T(1))
      : format("{percentage:3.0f}% {bar:40} {n}/{total} [{elapsed}<{remaining}, "
               "{rate}]"),
        n(0), total(total), step(step),
        tp(std::chrono::high_resolution_clock::now()) {}

  void tick() {
    {
      std::lock_guard<std::mutex> lock(thread_lock);
      if (n < total) {
        n += step;
        std::chrono::high_resolution_clock::time_point now_tp =
            std::chrono::high_resolution_clock::now();
        elapsed +=
            (std::chrono::duration_cast<std::chrono::nanoseconds>(now_tp - tp)
                 .count() /
             1e9f);
        tp = now_tp;
      }
    }
    display();
  }

  void display() {
    std::lock_guard<std::mutex> lock(thread_lock);
    std::string meter =
        format_meter(format, n, total, elapsed, unit, barchars[0], barchars[1],
                     barchars[2], barchars[3], barchars[4], unit_scale);
    std::fprintf(stdout, "%s", format_color(foreground_color).c_str());
    for (std::size_t i = 0; i < std::min(last_meter.size(), meter.size());
         ++i) {
      if (meter[i] != last_meter[i]) {
        last_meter[i] = meter[i];
        fmt::print("\033[{}G{}", i + 1, meter[i]);
      }
    }
    if (last_meter.size() < meter.size()) {
      fmt::print("\033[{}G", last_meter.size() + 1);
      for (std::size_t i = last_meter.size(); i < meter.size(); ++i) {
        last_meter.push_back(meter[i]);
        fmt::print("{}", meter[i]);
      }
    } else if (last_meter.size() > meter.size()) {
      fmt::print("\033[{}G", meter.size() + 1);
      std::size_t max_size = last_meter.size();
      for (std::size_t i = meter.size(); i < max_size; ++i) {
        last_meter.pop_back();
        fmt::print(" ");
      }
    }
    std::fprintf(stdout, "\033[1G\033[0m");
    std::fflush(stdout);
  }

  T size() const { return total; }

  void set_format(const std::string& new_format) { format = new_format; }
  void set_unit(const std::string& new_unit) { unit = new_unit; }
  void set_bar_chars(const std::string& new_barchars) {
    barchars = new_barchars;
  }
  void set_color(const Color& new_color) { foreground_color = new_color; }
  void set_unit_scale(const bool& setting) { unit_scale = setting; }

private:
  std::mutex thread_lock;
  std::string format;
  std::string unit = "it";
  std::string barchars = "[#> ]";
  Color foreground_color = BOLD;
  T n, total, step;
  float elapsed = 0.0f;
  bool unit_scale = false;
  std::chrono::high_resolution_clock::time_point tp;
  std::string last_meter = "";
};
} // namespace specula

#endif // SPECULA_DEV_TQDM_HPP_
