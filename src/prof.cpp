#include "specula/prof.hpp"

#include <fmt/format.h>

namespace specula {
namespace prof {
std::unordered_map<std::thread::id, std::stack<std::shared_ptr<profile_data>>>
    profile_stack;
std::unordered_map<
    std::thread::id,
    std::unordered_map<std::size_t, std::shared_ptr<profile_data>>>
    profile_store;
std::hash<std::thread::id> thread_hasher;
std::hash<std::string> key_hasher;
} // namespace prof
} // namespace specula

void specula::prof::print_profile_data(
    const std::shared_ptr<profile_data>& data, std::size_t indent,
    bool formatting) {
  std::string color_escape = "";
  std::string close_fmt = "";
  if (formatting) {
    uint8_t red = (data->color >> 16) & 0xFF;
    uint8_t green = (data->color >> 8) & 0xFF;
    uint8_t blue = (data->color) & 0xFF;
    color_escape = fmt::format("\033[1;38;2;{};{};{}m", red, green, blue);
    close_fmt = "\033[0m";
  }
  std::size_t instances = 0;
  double max_duration = 0.0f;
  double min_duration = std::numeric_limits<double>::infinity();
  double average_duration = 0.0f;
  double total_duration = 0.0f;
  for (std::size_t i = 0; i < data->time_points.size(); i += 2) {
    std::chrono::high_resolution_clock::duration interval =
        ((i != data->time_points.size() - 1)
             ? data->time_points[i + 1]
             : std::chrono::high_resolution_clock::now()) -
        data->time_points[i];
    double interval_seconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(interval).count() /
        1e9f;
    instances += 1;
    max_duration = std::max(max_duration, interval_seconds);
    min_duration = std::min(min_duration, interval_seconds);
    average_duration += interval_seconds;
    total_duration += interval_seconds;
  }
  average_duration /= instances;
  std::string indent_str = std::string(indent, ' ');
  fmt::print("{}{}{}({})[{}]:{} {} {} {} [{}]\n", indent_str, color_escape,
             data->name, data->catagory, instances, close_fmt, min_duration,
             average_duration, max_duration, total_duration);
  for (auto& prof_data : data->children) {
    print_profile_data(prof_data.second, indent + 2, formatting);
  }
}

void specula::prof::print_report(bool formatting) {
  for (auto& thread_store : profile_store) {
    if (formatting) {
      fmt::print("\033[1m{:0X}:\033[0m\n", thread_hasher(thread_store.first));
    } else {
      fmt::print("{:0X}:\n", thread_hasher(thread_store.first));
    }
    for (auto& prof_data : thread_store.second) {
      print_profile_data(prof_data.second, 2, formatting);
    }
  }
}