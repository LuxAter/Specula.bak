#include "specula/prof.hpp"

#include <thread>
#include <cstdio>

namespace specula {
namespace prof {
std::hash<std::thread::id> thread_hasher;
std::hash<const void*> pointer_hasher;
namespace fs {
FILE* file_stream = nullptr;
} // namespace fs
} // namespace prof
} // namespace specula

// namespace specula {
// namespace prof {
// std::unordered_map<std::thread::id,
// std::stack<std::shared_ptr<profile_data>>>
//     profile_stack;
// std::unordered_map<
//     std::thread::id,
//     std::unordered_map<std::size_t, std::shared_ptr<profile_data>>>
//     profile_store;
// std::hash<std::thread::id> thread_hasher;
// std::hash<std::string> key_hasher;
// } // namespace prof
// } // namespace specula
//
// void specula::prof::dump_to_file(const std::string& file) {
//   write_to_file(file);
//   profile_store.clear();
//   profile_stack.clear();
// }
// void specula::prof::dump_to_txt(const std::string& file) {
//   write_to_txt(file);
//   profile_store.clear();
//   profile_stack.clear();
// }
// void specula::prof::dump_to_csv(const std::string& file) {
//   write_to_csv(file);
//   profile_store.clear();
//   profile_stack.clear();
// }
// void specula::prof::dump_to_json(const std::string& file) {
//   write_to_json(file);
//   profile_store.clear();
//   profile_stack.clear();
// }
//
// void specula::prof::write_to_file(const std::string& file) {
//   if (0 == file.compare(file.length() - 4, 4, ".txt"))
//     write_to_txt(file);
//   else if (0 == file.compare(file.length() - 4, 4, ".csv"))
//     write_to_csv(file);
//   else if (0 == file.compare(file.length() - 5, 5, ".json"))
//     write_to_json(file);
// }
// void specula::prof::write_to_txt(const std::string& file) {
//   FILE* out = std::fopen(file.c_str(), "w");
//   for (auto& thread_store : profile_store) {
//     for (auto& prof_data : thread_store.second) {
//       write_profile_data_txt(out, prof_data.second);
//     }
//   }
//   std::fclose(out);
// }
// void specula::prof::write_to_csv(const std::string& file) {
//   FILE* out = std::fopen(file.c_str(), "w");
//   std::fprintf(out, "THREAD ID,TITLE,CATEGORY,START NS, STOP NS\n");
//   for (auto& thread_store : profile_store) {
//     for (auto& prof_data : thread_store.second) {
//       write_profile_data_csv(out, prof_data.second);
//     }
//   }
//   std::fclose(out);
// }
// void specula::prof::write_to_json(const std::string& file) {
//   FILE* out = std::fopen(file.c_str(), "w");
//   std::fprintf(out, "[");
//   for (auto& thread_store : profile_store) {
//     for (auto& prof_data : thread_store.second) {
//       write_profile_data_json(out, prof_data.second);
//     }
//   }
//   std::fclose(out);
// }
//
// void specula::prof::write_profile_data_txt(
//     FILE* out, const std::shared_ptr<profile_data>& data) {
//   for (std::size_t i = 0; i < data->time_points.size(); i += 2) {
//     std::fprintf(out, "%0X \"%s\" \"%s\" %lu %lu\n", data->tid,
//                  data->name.c_str(), data->category.c_str(),
//                  std::chrono::duration_cast<std::chrono::nanoseconds>(
//                      data->time_points[i].time_since_epoch())
//                      .count(),
//                  std::chrono::duration_cast<std::chrono::nanoseconds>(
//                      ((i != data->time_points.size() - 1)
//                           ? data->time_points[i + 1]
//                           : std::chrono::high_resolution_clock::now())
//                          .time_since_epoch())
//                      .count());
//   }
//   for (auto& child_data : data->children) {
//     write_profile_data_txt(out, child_data.second);
//   }
// }
// void specula::prof::write_profile_data_csv(
//     FILE* out, const std::shared_ptr<profile_data>& data) {
//   for (std::size_t i = 0; i < data->time_points.size(); i += 2) {
//     std::fprintf(out, "%0X,\"%s\",\"%s\",%lu,%lu\n", data->tid,
//                  data->name.c_str(), data->category.c_str(),
//                  std::chrono::duration_cast<std::chrono::nanoseconds>(
//                      data->time_points[i].time_since_epoch())
//                      .count(),
//                  std::chrono::duration_cast<std::chrono::nanoseconds>(
//                      ((i != data->time_points.size() - 1)
//                           ? data->time_points[i + 1]
//                           : std::chrono::high_resolution_clock::now())
//                          .time_since_epoch())
//                      .count());
//   }
//   for (auto& child_data : data->children) {
//     write_profile_data_csv(out, child_data.second);
//   }
// }
// void specula::prof::write_profile_data_json(
//     FILE* out, const std::shared_ptr<profile_data>& data) {
//   for (std::size_t i = 0; i < data->time_points.size(); i += 2) {
//     std::fprintf(out,
//                  "{\"pid\":1,\"tid\":%u,\"name\":\"%s\",\"cat\":\"%s\",\"ph\":"
//                  "\"X\",\"ts\":%lu,\"dur\":%lu},",
//                  data->tid, data->name.c_str(), data->category.c_str(),
//                  std::chrono::duration_cast<std::chrono::microseconds>(
//                      data->time_points[i].time_since_epoch())
//                      .count(),
//                  std::chrono::duration_cast<std::chrono::microseconds>(
//                      ((i != data->time_points.size() - 1)
//                           ? data->time_points[i + 1]
//                           : std::chrono::high_resolution_clock::now()) -
//                      data->time_points[i])
//                      .count());
//     // std::fprintf(
//     //     out,
//     //     "{\"pid\": 1,
//     \"tid\":%u,\"name\":\"%s\",\"cat\":\"%s\",\"ph\":\"B\",
//     //     "
//     //     "\"ts\": %lu},{\"pid\": 1,
//     \"tid\":%u,\"name\":\"%s\",\"cat\":\"%s\",
//     //     "
//     //     "\"ph\": \"E\", \"ts\":%lu},",
//     //     data->tid, data->name.c_str(), data->category.c_str(),
//     //     std::chrono::duration_cast<std::chrono::milliseconds>(
//     //         data->time_points[i].time_since_epoch())
//     //         .count(),
//     //     data->tid, data->name.c_str(), data->category.c_str(),
//     //     std::chrono::duration_cast<std::chrono::milliseconds>(
//     //         ((i != data->time_points.size() - 1)
//     //              ? data->time_points[i + 1]
//     //              : std::chrono::high_resolution_clock::now())
//     //             .time_since_epoch())
//     //         .count());
//   }
//   for (auto& child_data : data->children) {
//     write_profile_data_json(out, child_data.second);
//   }
// }
//
// void specula::prof::print_profile_data(
//     const std::shared_ptr<profile_data>& data, std::size_t indent,
//     bool formatting) {
//   std::string color_escape = "";
//   std::string close_fmt = "";
//   if (formatting) {
//     uint8_t red = (data->color >> 16) & 0xFF;
//     uint8_t green = (data->color >> 8) & 0xFF;
//     uint8_t blue = (data->color) & 0xFF;
//     color_escape = fmt::format("\033[1;38;2;{};{};{}m", red, green, blue);
//     close_fmt = "\033[0m";
//   }
//   std::size_t instances = 0;
//   double max_duration = 0.0f;
//   double min_duration = std::numeric_limits<double>::infinity();
//   double average_duration = 0.0f;
//   double total_duration = 0.0f;
//   for (std::size_t i = 0; i < data->time_points.size(); i += 2) {
//     std::chrono::high_resolution_clock::duration interval =
//         ((i != data->time_points.size() - 1)
//              ? data->time_points[i + 1]
//              : std::chrono::high_resolution_clock::now()) -
//         data->time_points[i];
//     double interval_seconds =
//         std::chrono::duration_cast<std::chrono::nanoseconds>(interval).count()
//         / 1e9f;
//     instances += 1;
//     max_duration = std::max(max_duration, interval_seconds);
//     min_duration = std::min(min_duration, interval_seconds);
//     average_duration += interval_seconds;
//     total_duration += interval_seconds;
//   }
//   average_duration /= instances;
//   std::string indent_str = std::string(indent, ' ');
//   fmt::print("{}{}{}({})[{}]:{} {} {} {} [{}]\n", indent_str, color_escape,
//              data->name, data->category, instances, close_fmt, min_duration,
//              average_duration, max_duration, total_duration);
//   for (auto& prof_data : data->children) {
//     print_profile_data(prof_data.second, indent + 2, formatting);
//   }
// }
//
// void specula::prof::print_report(bool formatting) {
//   for (auto& thread_store : profile_store) {
//     if (formatting) {
//       fmt::print("\033[1m{:0X}:\033[0m\n",
//       thread_hasher(thread_store.first));
//     } else {
//       fmt::print("{:0X}:\n", thread_hasher(thread_store.first));
//     }
//     for (auto& prof_data : thread_store.second) {
//       print_profile_data(prof_data.second, 2, formatting);
//     }
//   }
// }
