#ifndef SPECULA_UTIL_TIMER_HPP_
#define SPECULA_UTIL_TIMER_HPP_

#include <array>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace specula {
namespace util {
  namespace timer {
    void Start(uint8_t timer = 0);
    double Stop(uint8_t timer = 0);
    std::array<unsigned, 6> SplitTime(double sec);
    std::string FmtTime(double sec, uint8_t start = 1, uint8_t stop = 5,
                        bool trim = false, bool chars = true);
    double ETC(double avg, const unsigned long& remaining);
    double ETT(double avg, const unsigned long& total);
    std::string FmtETC(double avg, const unsigned long& remaining,
                       bool up_line = true);
    std::string FmtProc(double avg, const unsigned long& remaining,
                        const unsigned long& total, bool up_line = true);
  }  // namespace timer
}  // namespace util
}  // namespace specula

#endif  // SPECULA_UTIL_TIMER_HPP_
