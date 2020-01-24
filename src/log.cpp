#include "specula/log.hpp"

#include <iostream>
#include <memory>
#include <string>

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

static std::shared_ptr<spdlog::logger> logger;

bool specula::logger::initalize_logger(const LogLevel &console_level,
                                       const LogLevel &file_level) {
  try {
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    sinks.back()->set_level(
        static_cast<spdlog::level::level_enum>(console_level));
    sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "specula.log", true));
    sinks.back()->set_level(static_cast<spdlog::level::level_enum>(file_level));
    logger =
        std::make_shared<spdlog::logger>("specula", begin(sinks), end(sinks));
    logger->set_level(static_cast<spdlog::level::level_enum>(
        std::min(static_cast<uint8_t>(console_level),
                 static_cast<uint8_t>(file_level))));

    return true;
  } catch (const spdlog::spdlog_ex &ex) {
    std::cerr << "Log initialization failed: " << ex.what() << std::endl;
    return false;
  }
}

std::shared_ptr<spdlog::logger> specula::logger::get_logger() { return logger; }