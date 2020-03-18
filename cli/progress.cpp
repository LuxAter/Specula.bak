#include "progress.hpp"

#include <cmath>
#include <string>

#include <fmt/format.h>

std::string color(char spec) {
  switch (spec) {
  case 'k':
    return "\033[0;30m";
  case 'K':
    return "\033[0;1;30m";
  case 'r':
    return "\033[0;31m";
  case 'R':
    return "\033[0;1;31m";
  case 'g':
    return "\033[0;32m";
  case 'G':
    return "\033[0;1;32m";
  case 'y':
    return "\033[0;33m";
  case 'Y':
    return "\033[0;1;33m";
  case 'b':
    return "\033[0;34m";
  case 'B':
    return "\033[0;1;34m";
  case 'm':
    return "\033[0;35m";
  case 'M':
    return "\033[0;1;35m";
  case 'c':
    return "\033[0;36m";
  case 'C':
    return "\033[0;1;36m";
  case 'w':
    return "\033[0;37m";
  case 'W':
    return "\033[0;1;37m";
  case '*':
    return "\033[0;1;0m";
  default:
    return "\033[0m";
  }
}

std::string format_sizeof(const float &number) {
  float num = number;
  for (auto &&unit : {' ', 'k', 'M', 'G', 'T', 'P', 'E', 'Z'}) {
    if (std::abs(num) < 999.5) {
      if (std::abs(num) < 99.95) {
        if (std::abs(num) < 9.995) {
          return fmt::format("{:1.3f}", num) + unit;
        }
        return fmt::format("{:2.2f}", num) + unit;
      }
      return fmt::format("{:3.1f}", num) + unit;
    }
    num /= 1000;
  }
  return fmt::format("{0:3.1}Y", num);
}
std::string format_interval(const std::size_t &s) {
  auto mins_secs = std::div(s, 60);
  auto hours_mins = std::div(mins_secs.quot, 60);
  if (hours_mins.quot != 0) {
    return fmt::format("{0:d}:{1:02d}:{2:02d}", hours_mins.quot, hours_mins.rem,
                       mins_secs.rem);
  } else {
    return fmt::format("{0:02d}:{1:02d}", hours_mins.rem, mins_secs.rem);
  }
}

std::string progress::format(const std::string_view &desc,
                             const std::string_view &unit, const std::size_t &n,
                             const std::size_t &total, const float &elapsed,
                             const std::string_view &colors) {
  float frac = n / static_cast<float>(total);
  float rate = n / elapsed;
  float inv_rate = 1 / rate;
  std::string rate_noinv_str = format_sizeof(rate) + unit.data() + "/s";
  std::string rate_inv_str = format_sizeof(inv_rate) + "s/" + unit.data();
  std::string rate_str = inv_rate > 1 ? rate_inv_str : rate_noinv_str;
  float remaining = (total - n) / rate;

  std::string res =
      color(colors[0]) + fmt::format("{:10}", desc.data()) + color(colors[1]) +
      fmt::format(" {:3}% ", static_cast<std::uint8_t>(100 * frac));
  // std::size_t max_len = std::max(35 - static_cast<int>(desc.size()), 20);
  std::size_t max_len = 35;
  std::size_t bar_len = std::floor(frac * max_len);
  std::string bar(bar_len, '=');
  if (bar_len < max_len) {
    res += color(colors[2]) + '[' + color(colors[3]) + bar + color(colors[4]) +
           '>' + color(colors[5]) + std::string(max_len - bar_len - 1, '-') +
           color(colors[6]) + ']';
  } else {
    res += color(colors[2]) + '[' + color(colors[3]) + bar + color(colors[6]) +
           ']';
  }
  res += ' ' + color(colors[7]) + format_sizeof(n) + '/' + format_sizeof(total);
  res += ' ' + color(colors[0]) + '[' + color(colors[8]) +
         format_interval(elapsed) + '<' + format_interval(remaining) + ' ' +
         color(colors[9]) + rate_str + color(colors[0]) + ']';
  return res;
}
