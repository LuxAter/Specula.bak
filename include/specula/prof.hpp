#ifndef SPECULA_PROF_HPP_
#define SPECULA_PROF_HPP_

#ifdef ENABLE_PROF
#include <chrono>
#include <cstdio>
#include <fmt/format.h>
#include <thread>

#define PROF_STRINGIFY_IMPL(x) #x
#define PROF_STRINGIFY(x) PROF_STRINGIFY_IMPL(x)
#define PROF_CONCAT4_IMPL(a, b, c, d) a##b##c##d
#define PROF_CONCAT4(a, b, c, d) PROF_CONCAT4_IMPL(a, b, c, d)

#define PROF_FE0(func, obj, ...)
#define PROF_FE1(func, obj, x, ...)                                            \
  func(obj, x) PROF_FE0(func, obj, __VA_ARGS__)
#define PROF_FE2(func, obj, x, ...)                                            \
  func(obj, x) PROF_FE1(func, obj, __VA_ARGS__)
#define PROF_FE3(func, obj, x, ...)                                            \
  func(obj, x) PROF_FE2(func, obj, __VA_ARGS__)
#define PROF_FE4(func, obj, x, ...)                                            \
  func(obj, x) PROF_FE3(func, obj, __VA_ARGS__)
#define PROF_FE5(func, obj, x, ...)                                            \
  func(obj, x) PROF_FE4(func, obj, __VA_ARGS__)
#define PROF_FE6(func, obj, x, ...)                                            \
  func(obj, x) PROF_FE5(func, obj, __VA_ARGS__)
#define PROF_FE7(func, obj, x, ...)                                            \
  func(obj, x) PROF_FE6(func, obj, __VA_ARGS__)
#define PROF_FE8(func, obj, x, ...)                                            \
  func(obj, x) PROF_FE7(func, obj, __VA_ARGS__)
#define PROF_FE10(func, obj, x, ...)                                           \
  func(obj, x) PROF_FE9(func, obj, __VA_ARGS__)
#define PROF_GET_FE(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME
#define PROF_FOR_EACH(action, obj, ...)                                        \
  PROF_GET_FE(__VA_ARGS__, PROF_FE10, PROF_FE9, PROF_FE8, PROF_FE7, PROF_FE6,  \
              PROF_FE5, PROF_FE4, PROF_FE3, PROF_FE2, PROF_FE1, PROF_FE0)      \
  (action, obj, __VA_ARGS__)

#define PROF_SCOPED_NAME                                                       \
  PROF_CONCAT4(__ProfilerScoped_, __LINE__, _, __COUNTER__)
#define PROF_SCOPED_NAME_STR PROF_STRINGIFY(PROF_SCOPED_NAME)
#define PROF_FUNCTION __PRETTY_FUNCTION__

#define PROF_SCOPED(...)                                                       \
  specula::prof::ScopedProfiler PROF_SCOPED_NAME =                             \
      specula::prof::ScopedProfiler(__VA_ARGS__);
#define PROF_FUNC(...) PROF_SCOPED(PROF_FUNCTION)
#define PROF_FUNC_KEY(_0, val) , #val, val
#define PROF_FUNC_ARGS(...)                                                    \
  PROF_SCOPED(PROF_FUNCTION PROF_FOR_EACH(PROF_FUNC_KEY, obj, __VA_ARGS__));

#define PROF_BEGIN(...) specula::prof::event_begin(__VA_ARGS__);
#define PROF_END(...) specula::prof::event_end(__VA_ARGS__);
#define PROF_INST(...) specula::prof::event_instant(__VA_ARGS__);
#define PROF_COUNT(...) specula::prof::event_counter(__VA_ARGS__);

#define PROF_OBJ_CONSTRUCT(type, ptr)                                          \
  specula::prof::event_object_construct<type>(#type, ptr);
#define PROF_OBJECT_DESTRUCT(type, ptr)                                        \
  specula::prof::event_object_destroy<type>(#type, ptr);

#define PROF_KEY_VAL(obj, key) , #key, (obj)->key
#define PROF_SNAPSHOT(type, obj, ...)                                          \
  specula::prof::event_object_snapshot<type>(                                  \
      #type, obj PROF_FOR_EACH(PROF_KEY_VAL, obj, __VA_ARGS__));

#ifdef ENABLE_FILE_STREAM
#define PROF_STREAM_FILE(file) specula::prof::fs::open_stream_file(file);
#define PROF_CLOSE_STREAM() specula::prof::fs::close_stream_file();
#else
#define PROF_STREAM_FILE(file)
#define PROF_CLOSE_STREAM()
#endif // ENABLE_FILE_STREAM
#endif // ENABLE_PROF

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
inline void close_stream_file() {
  if (file_stream)
    std::fclose(file_stream);
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
template <typename T>
inline void event_object_construct(const std::string& key, const T* obj) {
  Event event{Event::EventType::OBJECT_CONSTRUCT,
              key,
              "",
              "",
              thread_hasher(std::this_thread::get_id()),
              pointer_hasher(reinterpret_cast<const void*>(obj))};
  handle_event(event);
}
template <typename T>
inline void event_object_destroy(const std::string& key, const T* obj) {
  Event event{Event::EventType::OBJECT_DESTROY,
              key,
              "",
              "",
              thread_hasher(std::this_thread::get_id()),
              pointer_hasher(reinterpret_cast<const void*>(obj))};
  handle_event(event);
}
template <typename T, typename... ARGS>
inline void event_object_snapshot(const std::string& key, const T* obj,
                                  const ARGS&... args) {
  Event event{Event::EventType::OBJECT_SNAPSHOT,
              key,
              "",
              fmt::format("\"snapshot\":{{{}}}", fmt_args(args...)),
              thread_hasher(std::this_thread::get_id()),
              pointer_hasher(reinterpret_cast<const void*>(obj))};
  handle_event(event);
}
struct ScopedProfiler {
  template <typename... ARGS>
  ScopedProfiler(const std::string& name, const ARGS&... args) {
    specula::prof::event_begin(name, args...);
  }
  ~ScopedProfiler() { specula::prof::event_end(); }
};
#endif // ENABLE_PROF
} // namespace prof
} // namespace specula

#endif // SPECULA_PROF_HPP_
