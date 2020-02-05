#ifndef SPECULA_ITERATOR_HPP
#define SPECULA_ITERATOR_HPP

#include <chrono>
#include <functional>
#include <type_traits>

#include <fmt/format.h>

#include "std/regex.hpp"

namespace specula {
namespace iter {
template <typename ValueType, typename Reference = ValueType&,
          typename Pointer = ValueType*>
class GenericIterator;
struct IterData {
  std::size_t n, total;
  float elapsed;
};

template <typename ValueType, typename Reference = ValueType&,
          typename Pointer = ValueType*>
class ReportingIterator {
public:
  ReportingIterator(const std::size_t& max_iterations,
                    const std::function<void(const IterData&)>& callback =
                        std::function<void(const IterData&)>())
      : current_iterations(0), max_iterations(max_iterations),
        callback(callback), seconds_elapsed(0.0f),
        tp(std::chrono::system_clock::now()) {}

  virtual std::size_t size() const noexcept { return max_iterations; }
  virtual GenericIterator<ValueType> begin() = 0;
  virtual GenericIterator<ValueType> end() = 0;
  virtual Reference get() = 0;
  virtual Pointer get_ptr() = 0;
  virtual std::size_t next(const int& steps = 1) = 0;

protected:
  void next_report(const std::size_t& steps) {
    current_iterations += steps;
    std::chrono::system_clock::time_point now_tp =
        std::chrono::system_clock::now();
    seconds_elapsed +=
        std::chrono::duration_cast<std::chrono::milliseconds>(now_tp - tp)
            .count() /
        1e3;
    tp = now_tp;
    if (callback)
      callback(
          IterData{current_iterations, max_iterations - 1, seconds_elapsed});
  }
  void reset_report() {
    current_iterations = 0;
    seconds_elapsed = 0;
    tp = std::chrono::system_clock::now();
    if (callback)
      callback(
          IterData{current_iterations, max_iterations - 1, seconds_elapsed});
  }

  std::size_t current_iterations, max_iterations;
  std::function<void(const IterData&)> callback;
  float seconds_elapsed;
  std::chrono::system_clock::time_point tp;
};

template <typename ValueType, typename Reference, typename Pointer>
class GenericIterator {
public:
  GenericIterator(ReportingIterator<ValueType, Reference, Pointer>* ptr,
                  std::size_t state)
      : ptr(ptr), state(state) {}
  inline bool operator==(const GenericIterator& it) const {
    return ptr == it.ptr && state == it.state;
  }
  inline bool operator!=(const GenericIterator& it) const {
    return ptr != it.ptr || state != it.state;
  }
  inline GenericIterator& operator++() {
    state = ptr->next();
    return *this;
  }

  inline Reference operator*() { return ptr->get(); }
  inline Pointer operator->() { return ptr->get_ptr(); }

private:
  ReportingIterator<ValueType, Reference, Pointer>* ptr;
  std::size_t state;
};

template <typename Container>
class ObjIter : public ReportingIterator<typename Container::value_type,
                                         typename Container::reference,
                                         typename Container::pointer> {
public:
  typedef typename Container::value_type value_type;
  typedef typename Container::reference reference;
  typedef typename Container::pointer pointer;

  ObjIter(Container& obj)
      : ReportingIterator<value_type, reference, pointer>(obj.size()),
        begin_iter(obj.begin()), end_iter(obj.end()),
        current_iter(obj.begin()) {}
  ObjIter(Container& obj, const std::function<void(const IterData&)>& callback)
      : ReportingIterator<value_type, reference, pointer>(obj.size(), callback),
        begin_iter(obj.begin()), end_iter(obj.end()),
        current_iter(obj.begin()) {}

  GenericIterator<value_type> begin() override {
    current_iter = begin_iter;
    return GenericIterator<value_type>(this, 0);
  }
  GenericIterator<value_type> end() override {
    return GenericIterator<value_type>(this, this->max_iterations);
  }
  reference get() override { return *current_iter; }
  pointer get_ptr() override { return &(*current_iter); }
  virtual std::size_t next(const int& steps = 1) override {
    this->next_report(steps);
    if (steps == 1) {
      current_iter++;
    } else {
      for (int i = 0; i < steps; ++i) {
        current_iter++;
      }
    }
    return this->current_iterations;
  }

protected:
  typename Container::iterator begin_iter, end_iter, current_iter;
};

template <typename Type>
class RangeIter : public ReportingIterator<Type, Type&, Type*> {
public:
  typedef Type value_type;
  typedef Type& reference;
  typedef Type* pointer;

  RangeIter(const Type& end)
      : ReportingIterator<value_type, reference, pointer>(
            static_cast<std::size_t>(end)),
        start_val(0), end_val(end), current_val(0), step_val(1) {}
  RangeIter(const Type& start, const Type& end)
      : ReportingIterator<value_type, reference, pointer>(
            (end > Type(1))
                ? static_cast<std::size_t>(end - start)
                : static_cast<std::size_t>((Type(1) - start) / end)),
        start_val(start), end_val((end > Type(1)) ? end : 1),
        current_val(start), step_val((end > Type(1)) ? 1 : end) {}
  RangeIter(const Type& start, const Type& end, const Type& step)
      : ReportingIterator<value_type, reference, pointer>(
            (end > step) ? static_cast<std::size_t>((end - start) / step)
                         : static_cast<std::size_t>((step - start) / end)),
        start_val(start), end_val((end > step) ? end : step),
        current_val(start), step_val((end > step) ? step : end) {}

  RangeIter(const Type& end,
            const std::function<void(const IterData&)>& callback)
      : ReportingIterator<value_type, reference, pointer>(
            static_cast<std::size_t>(end), callback),
        start_val(0), end_val(end), current_val(0), step_val(1) {}
  RangeIter(const Type& start, const Type& end,
            const std::function<void(const IterData&)>& callback)
      : ReportingIterator<value_type, reference, pointer>(
            (end > Type(1)) ? static_cast<std::size_t>(end - start)
                            : static_cast<std::size_t>((Type(1) - start) / end),
            callback),
        start_val(start), end_val((end > Type(1)) ? end : 1),
        current_val(start), step_val((end > Type(1)) ? 1 : end) {}
  RangeIter(const Type& start, const Type& end, const Type& step,
            const std::function<void(const IterData&)>& callback)
      : ReportingIterator<value_type, reference, pointer>(
            (end > step) ? static_cast<std::size_t>((end - start) / step)
                         : static_cast<std::size_t>((step - start) / end),
            callback),
        start_val(start), end_val((end > step) ? end : step),
        current_val(start), step_val((end > step) ? step : end) {}

  GenericIterator<value_type> begin() override {
    current_val = start_val;
    this->reset_report();
    return GenericIterator<value_type>(this, 0);
  }
  GenericIterator<value_type> end() override {
    return GenericIterator<value_type>(this, this->max_iterations);
  }
  reference get() override { return current_val; }
  pointer get_ptr() override { return &current_val; }
  virtual std::size_t next(const int& steps = 1) override {
    this->next_report(steps);
    if (steps == 1) {
      current_val += step_val;
    } else {
      for (int i = 0; i < steps; ++i) {
        current_val += step_val;
      }
    }
    return this->current_iterations;
  }

  value_type start_val, end_val, current_val, step_val;
};

class ProgressBarBase {
public:
  ProgressBarBase() {}
  static std::size_t display_len(const std::string& str) {
    std::size_t len = 0;
    bool skip = false;
    for (std::size_t i = 0; i < str.size(); ++i) {
      if (str[i] == '\033')
        skip = true;
      else if (skip && str[i] == 'm')
        skip = false;
      else
        len++;
    }
    return len;
  }
  static std::string format_sizeof(const float& number) {
    float num = number;
    for (auto&& unit : {' ', 'k', 'M', 'G', 'T', 'P', 'E', 'Z'}) {
      if (std::abs(num) < 999.5) {
        if (std::abs(num) < 99.95) {
          if (std::abs(num) < 9.995) {

            return fmt::format("{:1.2f}", num) + unit;
          }
          return fmt::format("{:2.1f}", num) + unit;
        }
        return fmt::format("{:3.0f}", num) + unit;
      }
      num /= 1000;
    }
    return fmt::format("{0:3.1}Y", num);
  }
  static std::string format_interval(const std::size_t& s) {
    auto mins_secs = std::div(s, 60);
    auto hours_mins = std::div(mins_secs.quot, 60);
    if (hours_mins.quot != 0) {
      return fmt::format("{0:d}:{1:02d}:{2:02d}", hours_mins.quot,
                         hours_mins.rem, mins_secs.rem);
    } else {
      return fmt::format("{0:02d}:{1:02d}", hours_mins.rem, mins_secs.rem);
    }
  }
  template <typename T> static std::string format_number(const T& num) {
    std::string f = fmt::format("{:.3g}", num);
    if (f.find("+0") != std::string::npos)
      f.replace(f.find("+0"), 2, "+");
    if (f.find("-0") != std::string::npos)
      f.replace(f.find("-0"), 2, "-");
    std::string n = fmt::format("{}", num);
    return (f.size() < n.size()) ? f : n;
  }
  static std::string format_color(const char& spec, const char& msg) {
    switch (spec) {
    case 'k':
      return fmt::format("\033[30m{}\033[0m", msg);
    case 'r':
      return fmt::format("\033[31m{}\033[0m", msg);
    case 'g':
      return fmt::format("\033[32m{}\033[0m", msg);
    case 'y':
      return fmt::format("\033[33m{}\033[0m", msg);
    case 'b':
      return fmt::format("\033[34m{}\033[0m", msg);
    case 'm':
      return fmt::format("\033[35m{}\033[0m", msg);
    case 'c':
      return fmt::format("\033[36m{}\033[0m", msg);
    case 'w':
      return fmt::format("\033[37m{}\033[0m", msg);
    case 'K':
      return fmt::format("\033[1;30m{}\033[0m", msg);
    case 'R':
      return fmt::format("\033[1;31m{}\033[0m", msg);
    case 'G':
      return fmt::format("\033[1;32m{}\033[0m", msg);
    case 'Y':
      return fmt::format("\033[1;33m{}\033[0m", msg);
    case 'B':
      return fmt::format("\033[1;34m{}\033[0m", msg);
    case 'M':
      return fmt::format("\033[1;35m{}\033[0m", msg);
    case 'C':
      return fmt::format("\033[1;36m{}\033[0m", msg);
    case 'W':
      return fmt::format("\033[1;37m{}\033[0m", msg);
    case '*':
      return fmt::format("\033[1m{}\033[0m", msg);
    default:
      return fmt::format("{:c}", msg);
    }
  }
  static std::string format_color(const char& spec, const std::string& msg) {
    switch (spec) {
    case 'k':
      return fmt::format("\033[30m{}\033[0m", msg);
    case 'r':
      return fmt::format("\033[31m{}\033[0m", msg);
    case 'g':
      return fmt::format("\033[32m{}\033[0m", msg);
    case 'y':
      return fmt::format("\033[33m{}\033[0m", msg);
    case 'b':
      return fmt::format("\033[34m{}\033[0m", msg);
    case 'm':
      return fmt::format("\033[35m{}\033[0m", msg);
    case 'c':
      return fmt::format("\033[36m{}\033[0m", msg);
    case 'w':
      return fmt::format("\033[37m{}\033[0m", msg);
    case 'K':
      return fmt::format("\033[1;30m{}\033[0m", msg);
    case 'R':
      return fmt::format("\033[1;31m{}\033[0m", msg);
    case 'G':
      return fmt::format("\033[1;32m{}\033[0m", msg);
    case 'Y':
      return fmt::format("\033[1;33m{}\033[0m", msg);
    case 'B':
      return fmt::format("\033[1;34m{}\033[0m", msg);
    case 'M':
      return fmt::format("\033[1;35m{}\033[0m", msg);
    case 'C':
      return fmt::format("\033[1;36m{}\033[0m", msg);
    case 'W':
      return fmt::format("\033[1;37m{}\033[0m", msg);
    case '*':
      return fmt::format("\033[1m{}\033[0m", msg);
    default:
      return msg;
    }
  }
  static std::string format_bar(const float& frac, const std::size_t len,
                                const std::string& chars = "[#>-]",
                                const std::string& colors = "*___*") {
    std::size_t bar_length = std::floor(frac * len);
    std::string bar(bar_length, chars[1]);
    if (bar_length < len) {
      return format_color(colors[0], chars[0]) + format_color(colors[1], bar) +
             format_color(colors[2], chars[2]) +
             format_color(colors[3],
                          std::string(len - bar_length - 1, chars[3])) +
             format_color(colors[4], chars[4]);
    } else {
      return format_color(colors[0], chars[0]) + format_color(colors[1], bar) +
             format_color(colors[4], chars[4]);
    }
  }

  template <typename T>
  static std::string
  format_meter(const std::string& format_spec, const T& n, const T& total,
               const float& elapsed, const bool& unit_scale,
               const std::string& desc, const std::string& unit,
               const std::string& bar_chars) {
    std::string elapsed_str = format_interval(elapsed);
    float rate = n / elapsed;
    float inv_rate = 1 / rate;
    std::string rate_noinv_str =
        (unit_scale ? format_sizeof(rate) : fmt::format("{:5.2f}", rate)) +
        unit + "/s";
    std::string rate_inv_str = (unit_scale ? format_sizeof(inv_rate)
                                           : fmt::format("{:5.2f}", inv_rate)) +
                               "s/" + unit;
    std::string rate_str = inv_rate > 1 ? rate_inv_str : rate_noinv_str;
    std::string n_str = unit_scale ? format_sizeof(n) : fmt::format("{}", n);
    std::string total_str =
        unit_scale ? format_sizeof(total) : fmt::format("{}", total);
    float remaining = (total - n) / rate;
    std::string remaining_str = format_interval(remaining);

    float frac = n / static_cast<float>(total);
    float percentage = frac * 100;

    std::string meter = format_spec;
    std::smatch results;
    try {
      std::regex tmp("\\{percentage\\}");
    } catch (std::regex_error& e) {
      LERROR("REGEX: {}", e.what());
    }
    meter = std::regex_replace(
        meter,
        std::regex("\\{percentage(:([0-9]+)?(\\.([0-9]+))?)?(;(["
                   "krgybmcwKRGYBMCW\\*_]+))?\\}"),
        [percentage](const std::smatch& match) {
          std::string fmt_spec =
              "{:" + (match[2].matched ? match[2].str() : "") +
              (match[4].matched ? "." + match[4].str() : "") + "}";
          return format_color(match[5].matched ? match[5].str()[0] : '_',
                              fmt::format(fmt_spec, percentage));
        });
    for (std::string&& key :
         {"n", "total", "elapsed", "remaining", "rate", "bar", "desc"}) {
      meter = std::regex_replace(
          meter,
          std::regex("\\{" + key +
                     "(:(<|^|>)?([0-9]+)?)?(;([krgybmcKRGYBMCW\\*_]+))?\\}"),
          [key, n_str, total_str, elapsed_str, remaining_str, rate_str, frac,
           bar_chars, desc](const std::smatch& match) {
            std::string val = "";
            char align = match[2].matched ? match[2].str()[0] : '>';
            int fmt_width = match[3].matched ? std::stoi(match[3]) : -1;
            std::string fmt_color = match[5].matched ? match[5].str() : "_____";
            if (key == "n") {
              val = n_str;
            } else if (key == "total") {
              val = total_str;
            } else if (key == "elapsed") {
              val = elapsed_str;
            } else if (key == "remaining") {
              val = remaining_str;
            } else if (key == "rate") {
              val = rate_str;
            } else if (key == "bar") {
              if (fmt_color.size() < 5) {
                fmt_color +=
                    std::string(5 - fmt_color.size(), fmt_color.back());
              }
              val = format_bar(frac, fmt_width != -1 ? fmt_width : 20,
                               bar_chars, fmt_color);
            } else if (key == "desc") {
              val = desc;
            }
            if (fmt_width != -1 &&
                static_cast<int>(display_len(val)) < fmt_width) {
              std::size_t str_disp_len = display_len(val);
              if (align == '<') {
                val = val + std::string(fmt_width - str_disp_len, ' ');
              } else if (align == '^') {
                val = std::string((fmt_width - str_disp_len) / 2, ' ') + val +
                      std::string((fmt_width - str_disp_len) / 2, ' ');

              } else {
                val = std::string(fmt_width - str_disp_len, ' ') + val;
              }
            }
            return format_color(fmt_color[0], val);
          });
      //   std::smatch match;
      //   if (std::regex_search(
      //           meter, match,
      //           std::regex(
      //               "{" + key +
      //               "(:(<|^|>)?([0-9]+)?)?(;([krgybmcKRGYBMCW\\*_]+))?}"))) {
      //     char align = match[2].matched ? match[2][0] : '>';
      //     int fmt_width = match[3].matched ? std::stoi(match[3]) : -1;
      //     std::string fmt_color = match[5].matched ? match[5] : "_____";
      //     if (key == "n") {
      //       value = n_str;
      //     } else if (key == "total") {
      //       value = total_str;
      //     } else if (key == "elapsed") {
      //       value = elapsed_str;
      //     } else if (key == "remaining") {
      //       value = remaining_str;
      //     } else if (key == "rate") {
      //       value = rate_str;
      //     } else if (key == "bar") {
      //       if (fmt_color.size() < 5) {
      //         fmt_color += std::string(5 - fmt_color.size(),
      //         fmt_color.back());
      //       }
      //       value = format_bar(frac, fmt_width != -1 ? fmt_width : 20,
      //       bar_chars,
      //                          fmt_color);
      //     } else if (key == "desc") {
      //       vlaue = desc;
      //     }
      //     if (fmt_width != -1 && static_cast<int>(display_len(value) <
      //     fmt_width) {
      //       std::size_t str_disp_len = display_len(value);
      //       if (align == "<") {
      //         value = value + std::string(fmt_width - str_disp_len, ' ');
      //       } else if (align == "^") {
      //         value = std::string((fmt_width - str_disp_len) / 2, ' ') +
      //         value +
      //                 std::string((fmt_width - str_disp_len) / 2, ' ');

      //       } else {
      //         value = std::string(fmt_width - str_disp_len, ' ') + value;
      //       }
      //     }
      //     meter.replace(match[0].first, match[0].second - match[0].first,
      //                   format_color(fmt_color[0], value));
      //   }
    }
    return meter;
  }

  ProgressBarBase& set_format(const std::string& new_format_spec) {
    format_spec = new_format_spec;
    return *this;
  }
  ProgressBarBase& set_description(const std::string& new_desc) {
    desc = new_desc;
    return *this;
  }
  ProgressBarBase& set_unit(const std::string& new_unit) {
    unit = new_unit;
    return *this;
  }
  ProgressBarBase& set_bar_chars(const std::string& new_bar_chars) {
    bar_chars = new_bar_chars;
    return *this;
  }
  ProgressBarBase& set_unit_scale(const bool& setting) {
    unit_scale = setting;
    return *this;
  }

  void set_base_offset(const std::size_t& offset) { base_offset = offset; }

protected:
  std::string format_spec =
      "{desc;W} {percentage:3.0}% {bar:40;WCCcW} {n}/{total} "
      "[{elapsed}<{remaining}, {rate;B}]";
  std::string desc = "";
  std::string unit = "it";
  std::string bar_chars = "[=>-]";
  bool unit_scale = false;

  std::size_t base_offset = 0;
}; // namespace iter

template <typename T, typename Enabled = void>
class ProgressBar : public ProgressBarBase {};
template <typename T>
class ProgressBar<T,
                  typename std::enable_if<!std::is_arithmetic<T>::value>::type>
    : public ProgressBarBase {
public:
  ProgressBar(T& obj)
      : obj_iter(new ObjIter<T>(
            obj, [this](const IterData& d) { this->display_meter(d); })) {}

  void display_meter(const IterData& data) {
    std::string meter =
        this->format_meter(this->format_spec, std::min(data.n, data.total),
                           data.total, data.elapsed, this->unit_scale,
                           this->desc, this->unit, this->bar_chars);
    if (first_print) {
      std::fprintf(stdout, "\n");
      first_print = false;
    }
    if (this->base_offset != 0)
      std::fprintf(stdout, "\033[%luF\033[2K\033[1G%s\033[0m",
                   this->base_offset, meter.c_str());
    else
      std::fprintf(stdout, "\033[2K\033[1G%s\033[0m", meter.c_str());
    std::fflush(stdout);
  }

  GenericIterator<typename T::value_type> begin() { return obj_iter->begin(); }
  GenericIterator<typename T::value_type> end() { return obj_iter->end(); }
  std::size_t size() { return obj_iter->size(); }

  inline void next() { obj_iter->next(); }

private:
  bool first_print = true;

  std::unique_ptr<ObjIter<T>> obj_iter;
};
template <typename T>
class ProgressBar<T,
                  typename std::enable_if<std::is_arithmetic<T>::value>::type>
    : public ProgressBarBase {
public:
  ProgressBar(const T& end)
      : range_iter(new RangeIter<T>(
            end, [this](const IterData& d) { this->display_meter(d); })) {}
  ProgressBar(const T& start, const T& end)
      : range_iter(new RangeIter<T>(start, end, [this](const IterData& d) {
          this->display_meter(d);
        })) {}
  ProgressBar(const T& start, const T& end, const T& step)
      : range_iter(
            new RangeIter<T>(start, end, step, [this](const IterData& d) {
              this->display_meter(d);
            })) {}

  void display_meter(const IterData& data) {
    std::string meter = this->format_meter(
        this->format_spec, range_iter->current_val + range_iter->step_val,
        range_iter->end_val, data.elapsed, this->unit_scale, this->desc,
        this->unit, this->bar_chars);
    if (this->base_offset != 0 && !first_print)
      std::fprintf(stdout, "\033[%luF\033[2K\033[1G%s\033[0m\033[%luE",
                   this->base_offset, meter.c_str(), this->base_offset);
    else
      std::fprintf(stdout, "\033[2K\033[1G%s\033[0m", meter.c_str());
    if (first_print) {
      std::fprintf(stdout, "\n");
      first_print = false;
    }
    std::fflush(stdout);
  }

  GenericIterator<T> begin() { return range_iter->begin(); }
  GenericIterator<T> end() { return range_iter->end(); }
  std::size_t size() { return range_iter->size(); }

  inline void next() { range_iter->next(); }

private:
  bool first_print = true;

  std::unique_ptr<RangeIter<T>> range_iter;
};

template <typename... BarTypes> class MultiBar {
public:
  MultiBar(BarTypes&&... new_bars) : bars(new_bars...) { set_offset<0>(); }
  template <std::size_t I> inline void next() { std::get<I>(bars).next(); }
  template <std::size_t I> inline std::size_t size() {
    return std::get<I>(bars).size();
  }
  template <std::size_t I>
  inline typename std::tuple_element<I, std::tuple<BarTypes...>>::type get() {
    return std::get<I>(bars);
  }

private:
  template <std::size_t I>
  inline typename std::enable_if<I == sizeof...(BarTypes)>::type set_offset() {}
  template <std::size_t I>
  inline typename std::enable_if<I != sizeof...(BarTypes)>::type set_offset() {
    std::get<I>(bars).set_base_offset(sizeof...(BarTypes) - I);
    set_offset<I + 1>();
  }
  std::tuple<BarTypes...> bars;
};

template <typename... T> inline ProgressBar<T...> make_progressbar(T... args) {
  return ProgressBar<T...>(args...);
}
template <typename... BarTypes>
inline MultiBar<BarTypes...> make_multibar(BarTypes&&... bars) {
  return MultiBar<BarTypes...>(bars...);
}
} // namespace iter
} // namespace specula

#endif // SPECULA_ITERATOR_HPP
