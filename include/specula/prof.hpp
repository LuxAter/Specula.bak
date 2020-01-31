#ifndef SPECULA_PROF_HPP_
#define SPECULA_PROF_HPP_

#ifdef ENABLE_PROF
#include <chrono>
#include <cstdio>
#include <fmt/format.h>
#include <thread>
#endif // ENABLE_PROF

#ifdef ENABLE_FILE_STREAM
#define STREAM_FILE(file) open_stream_file(file);
#else
#define STREAM_FILE(file)
#endif // ENABLE_FILE_STREAM

namespace specula {
namespace prof {
#ifdef ENABLE_PROF
struct Event {
  enum EventType {
    BEGIN,
    END,
    INSTANCE,
    COUNTER,
    OBJECT_CONSTRUCT,
    OBJECT_DESTROY,
    OBJECT_SNAPSHOT
  };

  inline static char get_type_char(const EventType& type) {
    switch (type) {
    case BEGIN:
    default:
      return 'B';
    case END:
      return 'E';
    case INSTANCE:
      return 'I';
    case COUNTER:
      return 'C';
    case OBJECT_CONSTRUCT:
      return 'N';
    case OBJECT_DESTROY:
      return 'D';
    case OBJECT_SNAPSHOT:
      return 'O';
    }
  }

  EventType type;
  const std::string name;
  const std::string cat;
  const std::string args;
  const std::size_t tid;
  const std::size_t id;
};
extern std::hash<std::thread::id> thread_hasher;
extern std::hash<const void*> pointer_hasher;

#ifdef ENABLE_FILE_STREAM
namespace fs {
extern FILE* file_stream;
inline void open_stream_file(const char* file) {
  file_stream = std::fopen(file, "w");
  std::fprintf(file_stream, "[");
}
inline void handle_event(const Event& event) {
  if (!file_stream)
    open_stream_file("profile.json");
  fmt::print(
      file_stream, "{{{}{}\"ph\":\"{}\",\"ts\":{},\"pid\":1,\"tid\":{}{}{}}},",
      (event.name.size() == 0) ? ""
                               : fmt::format("\"name\":\"{}\",", event.name),
      (event.cat.size() == 0) ? "" : fmt::format("\"cat\":\"{}\",", event.cat),
      Event::get_type_char(event.type),
      std::chrono::duration_cast<std::chrono::microseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch())
          .count(),
      event.tid,
      (event.id == 0) ? "" : fmt::format(",\"id\":\"0x{:X}\"", event.id),
      (event.args.size() == 0) ? ""
                               : fmt::format(",\"args\":{{{}}}", event.args));
}
} // namespace fs
#endif // ENABLE_FILE_STREAM

inline std::string fmt_args() { return ""; }
template <typename T>
inline std::string fmt_args(const std::string& key, const T& v) {
  return fmt::format("\"{}\": {}", key, v);
}
template <>
inline std::string fmt_args(const std::string& key, const std::string& v) {
  return fmt::format("\"{}\": \"{}\"", key, v);
}
template <typename T, typename... ARGS>
inline std::string fmt_args(const std::string& key, const T& v,
                            const ARGS&... args) {
  return fmt::format("{}, \"{}\": {}", fmt_args(args...), key, v);
}
template <typename... ARGS>
inline std::string fmt_args(const std::string& key, const std::string& v,
                            const ARGS&... args) {
  return fmt::format("{}, \"{}\": \"{}\"", fmt_args(args...), key, v);
}
inline std::pair<std::string, std::string> split_cat_args() {
  return std::make_pair("", "");
}
template <typename... ARGS>
inline typename std::enable_if<(sizeof...(ARGS)) % 2 == 0,
                               std::pair<std::string, std::string>>::type
split_cat_args(const std::string& cat, const ARGS&... args) {
  return std::make_pair(cat, fmt_args(args...));
}
template <typename... ARGS>
inline typename std::enable_if<(sizeof...(ARGS)) % 2 != 0,
                               std::pair<std::string, std::string>>::type
split_cat_args(const std::string& cat, const ARGS&... args) {
  return std::make_pair("", fmt_args(cat, args...));
}

inline void handle_event(const Event& event) {
#ifdef ENABLE_FILE_STREAM
  fs::handle_event(event);
#endif // ENABLE_FILE_STREAM
}

template <typename... ARGS>
inline void event_begin(const std::string& name, const ARGS&... args) {
  auto cat_args = split_cat_args(args...);
  Event event{Event::EventType::BEGIN,
              name,
              cat_args.first,
              cat_args.second,
              thread_hasher(std::this_thread::get_id()),
              0};
  handle_event(event);
}
template <typename... ARGS> inline void event_end(const ARGS&... args) {
  Event event{Event::EventType::END,
              "",
              "",
              fmt_args(args...),
              thread_hasher(std::this_thread::get_id()),
              0};
  handle_event(event);
}
template <typename... ARGS>
inline void event_instant(const std::string& name, const ARGS&... args) {
  auto cat_args = split_cat_args(args...);
  Event event{Event::EventType::INSTANCE,
              name,
              cat_args.first,
              cat_args.second,
              thread_hasher(std::this_thread::get_id()),
              0};
  handle_event(event);
}
template <typename... ARGS>
inline void event_counter(const std::string& name, const ARGS&... args) {
  Event event{Event::EventType::COUNTER,
              name,
              "",
              fmt_args(args...),
              thread_hasher(std::this_thread::get_id()),
              0};
  handle_event(event);
}
template <typename T> inline void event_object_construct(const T* obj) {
  std::string pretty_func(__PRETTY_FUNCTION__);
  Event event{Event::EventType::OBJECT_CONSTRUCT,
              pretty_func.substr(63, pretty_func.length() - 64),
              "",
              "",
              thread_hasher(std::this_thread::get_id()),
              pointer_hasher(reinterpret_cast<const void*>(obj))};
  handle_event(event);
}
template <typename T> inline void event_object_destroy(const T* obj) {
  std::string pretty_func(__PRETTY_FUNCTION__);
  Event event{Event::EventType::OBJECT_DESTROY,
              pretty_func.substr(61, pretty_func.length() - 62),
              "",
              "",
              thread_hasher(std::this_thread::get_id()),
              pointer_hasher(reinterpret_cast<const void*>(obj))};
  handle_event(event);
}
template <typename T, typename... ARGS>
inline void event_object_snapshot(const T* obj, const ARGS&... args) {
  std::string pretty_func(__PRETTY_FUNCTION__);
  Event event{
      Event::EventType::OBJECT_SNAPSHOT,
      pretty_func.substr(79, pretty_func.find(';', 79) - 79),
      "",
      fmt::format("\"snapshot\":{{{}}}", fmt_args(args...)),
      thread_hasher(std::this_thread::get_id()),
      pointer_hasher(reinterpret_cast<const void*>(obj))};
  handle_event(event);
}
#endif // ENABLE_PROF
} // namespace prof
} // namespace specula

#endif // SPECULA_PROF_HPP_
