#ifndef SPECULA_CLI_PROGRESS_HPP_
#define SPECULA_CLI_PROGRESS_HPP_

#include <functional>
#include <map>
#include <string>
#include <vector>

#include <iostream>

namespace progress {
std::string format(const std::string_view &desc, const std::string_view &unit,
                   const std::size_t &n, const std::size_t &total,
                   const float &elapsed, const std::string_view &colors);

struct MultiBar {
public:
  MultiBar()
      : bars(), color_sets({"K.WCCcW.cC", "K.WMMmW.mM", "K.WBBbW.bB",
                            "K.WYYyW.yY", "K.WGGgW.gG"}) {}

  inline std::function<void(const std::size_t &, const std::string_view &,
                            const std::string_view &, const std::size_t &,
                            const std::size_t &, const float &)>
  callback() {
    return [this](const std::size_t &uuid, const std::string_view &desc,
                  const std::string_view &unit, const std::size_t &n,
                  const std::size_t &total, const float &elapsed) {
      this->internal_callback(uuid, desc, unit, n, total, elapsed);
    };
  }
  inline void internal_callback(const std::size_t &uuid,
                                const std::string_view &desc,
                                const std::string_view &unit,
                                const std::size_t &n, const std::size_t &total,
                                const float &elapsed) {
    for (std::size_t i = 0; i < bars.size(); ++i) {
      if (bars[i] == uuid) {
        if (i == max_lines - 1) {
          std::fprintf(stdout, "\033[G\033[2K%s",
                       format(desc, unit, n, total, elapsed,
                              color_sets[i % color_sets.size()])
                           .c_str());
        } else {
          std::fprintf(stdout, "\033[%luF\033[2K%s\033[%luE", max_lines - i - 1,
                       format(desc, unit, n, total, elapsed,
                              color_sets[i % color_sets.size()])
                           .c_str(),
                       max_lines - i - 1);
        }
        std::fflush(stdout);
        if (n >= total)
          bars.erase(bars.begin() + i);
        return;
      }
    }
    if (bars.size() >= max_lines) {
      max_lines++;
      std::fprintf(stdout, "\n");
    }
    std::fprintf(stdout, "\033[G\033[2K%s",
                 format(desc, unit, n, total, elapsed,
                        color_sets[bars.size() % color_sets.size()])
                     .c_str());
    std::fflush(stdout);
    if (n != total)
      bars.push_back(uuid);
    return;
  }

private:
  std::size_t max_lines = 0;
  std::vector<std::size_t> bars;
  std::vector<std::string> color_sets;
};
} // namespace progress

#endif /* end of include guard: SPECULA_CLI_PROGRESS_HPP_ */
