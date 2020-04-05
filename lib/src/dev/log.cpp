#include "dev/log.hpp"
#include "spdlog/common.h"

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

static std::vector<spdlog::sink_ptr> core_sinks;

static std::shared_ptr<spdlog::logger> core_logger;
static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>>
    client_logger;

void specula::logger::push_sink(const spdlog::sink_ptr &sink,
                                const LogLevel &sink_level) {
  sink->set_level(static_cast<spdlog::level::level_enum>(sink_level));
  core_sinks.push_back(sink);
}

bool specula::logger::initialize_core_logger() {
  try {
    core_logger = std::make_shared<spdlog::logger>("specula", begin(core_sinks),
                                                   end(core_sinks));
    core_logger->set_level(spdlog::level::trace);
    spdlog::set_level(spdlog::level::trace);
    return true;
  } catch (const spdlog::spdlog_ex &ex) {
    std::cerr << "Log initialization failed: " << ex.what() << std::endl;
    return false;
  }
}

bool specula::logger::initialize_logger(const std::string &name) {
  try {
    client_logger[name] = std::make_shared<spdlog::logger>(
        name, begin(core_sinks), end(core_sinks));
    client_logger[name]->set_level(spdlog::level::trace);

    return true;
  } catch (const spdlog::spdlog_ex &ex) {
    std::cerr << "Log initialization failed: " << ex.what() << std::endl;
    return false;
  }
}

bool specula::logger::terminate_logger(const std::string &name) {
  if (!client_logger.empty() &&
      client_logger.find(name) != client_logger.end()) {
    client_logger.erase(client_logger.find(name));
    return true;
  }
  std::cerr
      << "Failed to pop logger from stack, other loggers have been pushed";
  return false;
}

std::shared_ptr<spdlog::logger> specula::logger::get_core() {
  return core_logger;
}
std::shared_ptr<spdlog::logger>
specula::logger::get_client(const std::string &name) {
  return client_logger[name];
}
