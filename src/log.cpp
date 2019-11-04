#include "log.hpp"

#include <iostream>
#include <memory>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

bool specula::log::initalize_logger(const std::size_t &verbosity) {
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    switch (verbosity) {
      case 0:
        console_sink->set_level(spdlog::level::trace);
        break;
      case 1:
        console_sink->set_level(spdlog::level::debug);
        break;
      case 2:
        console_sink->set_level(spdlog::level::info);
        break;
      case 3:
        console_sink->set_level(spdlog::level::warn);
        break;
      case 4:
        console_sink->set_level(spdlog::level::err);
        break;
      case 5:
        console_sink->set_level(spdlog::level::critical);
        break;
      case 6:
        console_sink->set_level(spdlog::level::off);
        break;
    }

    auto file_sink =
        std::make_shared<spdlog::sinks::basic_file_sink_mt>("specula.log", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::set_default_logger(std::make_shared<spdlog::logger>(
        "specula", spdlog::sinks_init_list({console_sink, file_sink})));
    spdlog::set_level(spdlog::level::trace);

    return true;
  } catch (const spdlog::spdlog_ex &ex) {
    std::cerr << "Log initialization failed: " << ex.what() << std::endl;
    return false;
  }
}
