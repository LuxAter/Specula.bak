#ifndef FMT_HPP_
#define FMT_HPP_

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace fmt {

template <std::size_t _I, typename _T>
std::string __fmt(const std::string &fmt_str, const _T &arg) {
  std::string res = fmt_str;
  std::size_t pos = 0;
  bool specified_id = false;
  while ((pos = res.find("{", pos)) != std::string::npos) {
    if (res.size() <= pos + 1) {
      throw std::invalid_argument("Expected closing '}' for format specifier");
    } else if (res[pos + 1] == '{') {
      pos += 2;
      continue;
    }
    std::size_t ch = pos + 1;
    std::size_t id = _I;
    char fill_char = ' ', alignment = 2;
    std::size_t padding = 0, perc = 5;
    if (res[ch] >= '0' && res[ch] <= '9') {
      id = 0;
      while (res.size() > ch && res[ch] >= '0' && res[ch] <= '9') {
        id = (id * 10) + (res[ch] - '0');
        ch++;
      }
      if (res.size() <= ch) {
        throw std::invalid_argument(
            "Expected closing '}' for format specifier");
      }
    } else if (specified_id) {
      pos++;
      continue;
    } else {
      specified_id = true;
    }
    if (id != _I) {
      pos++;
      continue;
    }

    if (res[ch] == ':') {
      ch++;
      fill_char = ' ';
      if (res[ch] != '}' && !(res[ch] >= '1' && res[ch] <= '9')) {
        fill_char = res[ch];
        ch++;
      }
      if (res.size() <= ch) {
        throw std::invalid_argument(
            "Expected closing '}' for format specifier");
      }

      padding = 0;
      while (res.size() > ch && res[ch] >= '0' && res[ch] <= '9') {
        padding = (padding * 10) + (res[ch] - '0');
        ch++;
      }
      if (res.size() <= ch) {
        throw std::invalid_argument(
            "Expected closing '}' for format specifier");
      }

      if (res[ch] == '.') {
        ch++;
        perc = 0;
        while (res.size() > ch && res[ch] >= '0' && res[ch] <= '9') {
          perc = (perc * 10) + (res[ch] - '0');
          ch++;
        }
        if (res.size() <= ch) {
          throw std::invalid_argument(
              "Expected closing '}' for format specifier");
        }
      }
      if (res[ch] == '<' || res[ch] == '=' || res[ch] == '>') {
        alignment = res[ch] - '<';
        ch++;
      }
    } else if (res[ch] != '}') {
      throw std::invalid_argument(
          std::string(
              "Expected format specifier token of either ':'/'}' but was '") +
          res[ch] + "'");
    }
    if (res[ch] == '}') {
      std::stringstream ss;
      ss << std::setprecision(perc + 1) << arg;
      std::string arg_str = ss.str();
      if (arg_str.size() < padding) {
        if (alignment == 0) {
          arg_str = arg_str + std::string(padding - arg_str.size(), fill_char);
        } else if (alignment == 1) {
          arg_str =
              std::string(static_cast<std::size_t>(
                              std::ceil((padding - arg_str.size()) / 2.0)),
                          fill_char) +
              arg_str +
              std::string(static_cast<std::size_t>(
                              std::floor((padding - arg_str.size()) / 2.0)),
                          fill_char);
        } else {
          arg_str = std::string(padding - arg_str.size(), fill_char) + arg_str;
        }
      }
      res.replace(pos, ch - pos + 1, arg_str);
    } else {
      throw std::invalid_argument(
          std::string("Expected format specifier token of '}' but was '") +
          res[ch] + "'");
    }
    pos++;
  }
  return res;
}

template <std::size_t _I = 0>
inline std::string fmt(const std::string &fmt_str) {
  std::string res = fmt_str;
  std::size_t pos = 0;
  if ((pos = res.find("{")) != std::string::npos && res.size() > pos + 1 &&
      res[pos + 1] != '{') {
    throw std::invalid_argument("Expected at least one parameter");
  }
  return res;
}

template <std::size_t _I = 0, typename _T>
std::string fmt(const std::string &fmt_str, const _T &arg) {
  if (_I == 0) {
    std::string res = __fmt<_I>(fmt_str, arg);
    std::size_t pos = 0;
    while ((pos = res.find("{{", pos + 1)) != std::string::npos) {
      res.replace(pos, 2, "{");
    }
    while ((pos = res.find("}}", pos + 1)) != std::string::npos) {
      res.replace(pos, 2, "}");
    }
    return res;
  } else {
    return __fmt<_I>(fmt_str, arg);
  }
}

template <std::size_t _I = 0, typename _T, typename... _ARGS>
std::string fmt(const std::string &fmt_str, const _T &arg,
                const _ARGS &... args) {
  if (_I == 0) {
    std::string res = fmt<_I + 1>(__fmt<_I>(fmt_str, arg), args...);
    std::size_t pos = 0;
    while ((pos = res.find("{{", pos + 1)) != std::string::npos) {
      res.replace(pos, 2, "{");
    }
    while ((pos = res.find("}}", pos + 1)) != std::string::npos) {
      res.replace(pos, 2, "}");
    }
    return res;
  } else {
    return fmt<_I + 1>(__fmt<_I>(fmt_str, arg), args...);
  }
}

inline std::string wrap(const std::string &msg, std::size_t indent = 2,
                        std::size_t width = 80) {
  std::string res = msg;
  std::size_t pos = 0;
  std::size_t line_len = 0;
  std::string line_split = '\n' + std::string(indent, ' ');
  while ((pos = res.find(' ', pos)) != std::string::npos) {
    if (pos - line_len + indent >= width) {
      std::size_t prev = res.rfind(' ', pos - 1);
      res.replace(prev, 1, line_split);
      pos += line_split.size();
      line_len = prev + line_split.size();
    }
    pos++;
  }
  return res;
}

} // namespace fmt

#endif // FMT_HPP_
