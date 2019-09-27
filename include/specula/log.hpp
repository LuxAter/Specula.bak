#ifndef SPECULA_LOG_HPP_
#define SPECULA_LOG_HPP_

// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#include <array>
#include <ctime>
#include <string>
#include <string_view>

#include "specula/fmt.hpp"
#include "specula/fs.hpp"

#define lfatal(msg, ...)                                                       \
  log::Logger::get()->_log(specula::log::FATAL, msg, __FILE__, __func__,       \
                           __LINE__, ##__VA_ARGS__)
#define lerror(msg, ...)                                                       \
  log::Logger::get()->_log(specula::log::ERROR, msg, __FILE__, __func__,       \
                           __LINE__, ##__VA_ARGS__)
#define lwarning(msg, ...)                                                     \
  log::Logger::get()->_log(specula::log::WARNING, msg, __FILE__, __func__,     \
                           __LINE__, ##__VA_ARGS__)
#define lstatus(msg, ...)                                                      \
  log::Logger::get()->_log(specula::log::STATUS, msg, __FILE__, __func__,      \
                           __LINE__, ##__VA_ARGS__)
#define lsuccess(msg, ...)                                                     \
  log::Logger::get()->_log(specula::log::SUCCESS, msg, __FILE__, __func__,     \
                           __LINE__, ##__VA_ARGS__)
#define ldebug(msg, ...)                                                       \
  log::Logger::get()->_log(specula::log::LOG_DEBUG, msg, __FILE__, __func__,   \
                           __LINE__, ##__VA_ARGS__)
#define linfo(msg, ...)                                                        \
  log::Logger::get()->_log(specula::log::INFO, msg, __FILE__, __func__,        \
                           __LINE__, ##__VA_ARGS__)
#define lversion(msg, ...)                                                     \
  log::Logger::get()->_log(specula::log::VERSION, msg, __FILE__, __func__,     \
                           __LINE__, ##__VA_ARGS__)
#define ldatetime(msg, ...)                                                    \
  log::Logger::get()->_log_timestamp(__FILE__, __func__, __LINE__,             \
                                     ##__VA_ARGS__)

namespace specula {
namespace log {
enum LogType {
  FATAL,
  ERROR,
  WARNING,
  STATUS,
  SUCCESS,
  LOG_DEBUG,
  INFO,
  VERSION,
  TIMESTAMP
};
static const std::array<std::string, 9> log_type_str_ = {
    "FATAL", "ERROR", "WARNING", "STATUS",   "SUCCESS",
    "DEBUG", "INFO",  "VERSION", "TIMESTAMP"};

class Logger {
public:
  inline static Logger *get() {
    static Logger instance;
    return &instance;
  }

  inline void file_log(const LogType &type, const std::string_view &msg) {
    if (log_daily_file_ == nullptr) {
      if (!fs::exists(file_prefix_)) {
        fs::create_directory(file_prefix_);
      }
      time_t now = time(nullptr);
      struct tm tstruct = *localtime(&now);
      log_daily_file_ =
          std::fopen(fmt::format("%s/%04d.%02d.%02d.log", file_prefix_.c_str(),
                                 tstruct.tm_year + 1900, tstruct.tm_mon + 1,
                                 tstruct.tm_mday)
                         .c_str(),
                     "a");
      if (log_daily_file_ == nullptr)
        throw std::logic_error("Failed to create log file");
    }
    std::fprintf(log_daily_file_, "%s\n", msg.data());
    if (type < verbosity_)
      std::fflush(log_daily_file_);
  }

  inline void console_log(const LogType &type, const std::string_view &msg) {
    if (type >= verbosity_)
      return;
    switch (type) {
    case FATAL:
    case ERROR:
      printf("\033[1;31m%s\033[0m\n", msg.data());
      break;
    case WARNING:
    case VERSION:
      printf("\033[1;33m%s\033[0m\n", msg.data());
      break;
    case STATUS:
      printf("\033[1;34m%s\033[0m\n", msg.data());
      break;
    case SUCCESS:
      printf("\033[1;32m%s\033[0m\n", msg.data());
      break;
    case LOG_DEBUG:
      printf("\033[1;35m%s\033[0m\n", msg.data());
      break;
    case INFO:
    case TIMESTAMP:
      printf("\033[1;37m%s\033[0m\n", msg.data());
      break;
    default:
      printf("%s", msg.data());
      break;
    }
  }

  inline void _log(const LogType &type, const std::string &message,
                   const std::string &file, const std::string &func,
                   const unsigned long line, ...) {
    va_list args;
    va_start(args, line);
    const std::string body = fmt::format(message, args);
    va_end(args);
    const std::string location =
        fmt::format("%s:%s:%lu", file.substr(file.find("Specula")).c_str(),
                    func.c_str(), line);
    const std::string log_msg =
        fmt::format("[%s] (%s) %s", log_type_str_[type].c_str(),
                    location.c_str(), body.c_str());
    if (console_default_) {
      console_log(type, log_msg);
    }
    if (file_default_) {
      file_log(type, log_msg);
    }
  }

  inline void _log_timestamp(const std::string &file, const std::string &func,
                             const unsigned long line) {
    time_t current = std::time(nullptr);
    char buff[255];
    std::strftime(buff, 255, "%c", localtime(&current));
    _log(specula::log::TIMESTAMP, "%s (%lu)", file, func, line, buff, current);
  }

#ifdef DEBUG
  bool console_default_ = true;
  unsigned verbosity_ = 10;
#else
  bool console_default_ = false;
  unsigned verbosity_ = 3;
#endif
  bool file_default_ = true;
  std::string file_prefix_ = "logs/";
  FILE *log_daily_file_ = nullptr;
};

inline static void set_prefix(const std::string &prefix) {
  Logger::get()->file_prefix_ = prefix;
}
inline static void console(const bool &setting) {
  Logger::get()->console_default_ = setting;
}
inline static void file(const bool &setting) {
  Logger::get()->file_default_ = setting;
}
inline static void verbosity(const unsigned &setting) {
  Logger::get()->verbosity_ = setting;
}

} // namespace log
} // namespace specula

// #pragma clang diagnostic pop

#endif // SPECULA_LOG_HPP_
