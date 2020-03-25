#ifndef SPECULA_DEV_PROF_HPP_
#define SPECULA_DEV_PROF_HPP_

#include <cstdio>
#include <string>
#include <thread>

#ifdef __PROFILER__
#include <chrono>
#include <typeinfo>
#include <vector>

#include <fmt/format.h>

#include "../global/compiler.hpp"

#define SPECULA_PROF_CONCAT_IMPL(a, b, c, d) a##b##c##d
#define SPECULA_PROF_CONCAT(a, b, c, d) SPECULA_PROF_CONCAT_IMPL(a, b, c, d)
#define SPECULA_PROF_STRINGIFY_IMPL(x) #x
#define SPECULA_PROF_STRINGIFY(x) SPECULA_PROF_STRINGIFY_IMPL(x)

#define SPECULA_PROF_FUNCTION_NAME __PRETTY_FUNCTION__
#define SPECULA_PROFILER_NAME                                                  \
  SPECULA_PROF_CONCAT(__PROFILER_, __COUNTER__, _, __LINE__)

#define SPECULA_PROF_FE0(func, obj, ...)
#define SPECULA_PROF_FE1(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE0(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE2(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE1(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE3(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE2(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE4(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE3(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE5(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE4(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE6(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE5(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE7(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE6(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE8(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE7(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE9(func, obj, x, ...)                                    \
  func(obj, x) SPECULA_PROF_FE8(func, obj, __VA_ARGS__)
#define SPECULA_PROF_FE10(func, obj, x, ...)                                   \
  func(obj, x) SPECULA_PROF_FE9(func, obj, __VA_ARGS__)
#define SPECULA_PROF_GET_FE(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) \
  NAME
#define SPECULA_PROF_FOREACH(func, obj, ...)                                   \
  SPECULA_GET_FE(__VA_ARGS__, SPECULA_PROF_FE10, SPECULA_PROF_FE9,             \
                 SPECULA_PROF_FE8, SPECULA_PROF_FE7, SPECULA_PROF_FE6,         \
                 SPECULA_PROF_FE5, SPECULA_PROF_FE4, SPECULA_PROF_FE3,         \
                 SPECULA_PROF_FE2, SPECULA_PROF_FE1, SPECULA_PROF_FE0)         \
  (func, obj, __VA_ARGS__)

#define SPECULA_PROF_SCOPED_NAME                                               \
  SPECULA_PROF_CONCAT(__ProfilerScoped_, __LINE__, _, __COUNTER__)
#define SPECULA_PROF_SCOPED_NAME_STR                                           \
  SPECULA_PROF_STRINGIFY(SPECULA_PROF_SCOPED_NAME)
#define SPECULA_PROF_FUNCTION __PRETTY_FUNCTION__

#define SPECULA_PROF_FUNC_KEY(_0, val) , #val, val
#define SPECULA_PROF_KEY_VAL(obj, key) , #key, (obj)->key

#define PROF_SCOPED(...)                                                       \
  specula::prof::ScopedProfiler SPECULA_PROF_SCOPED_NAME =                     \
      specula::prof::ScopedProfiler(__VA_ARGS__);
#define PROF_FUNC(...)                                                         \
  specula::prof::ScopedProfiler SPECULA_PROF_SCOPED_NAME =                     \
      specula::prof::ScopedProfiler(SPECULA_PROF_FUNCTION, __VA_ARGS__);
#define PROF_FUNC_ARGS(...)                                                    \
  specula::prof::ScopedProfiler SPECULA_PROF_SCOPED_NAME =                     \
      specula::prof::ScopedProfiler(                                           \
          SPECULA_PROF_FUNCTION,                                               \
          SPECULA_PROF_FOREACH(SPECULA_PROF_FUNC_KEY, obj, __VA_ARGS__));

#define PROF_BEGIN(...) specula::prof::event_begin(__VA_ARGS__);
#define PROF_END(...) specula::prof::event_end(__VA_ARGS__);
#define PROF_INST(...) specula::prof::event_instant(__VA_ARGS__);
#define PROF_COUNTER(...) specula::prof::event_counter(__VA_ARGS__);
#define PROF_COUNT(...) specula::prof::event_counter("Counters", __VA_ARGS__);

#define PROF_OBJ(type) specula::prof::ObjectProfiler<type>
#define PROF_OBJ_CONSTRUCT(ptr) specula::prof::event_object_construct(ptr);
#define PROF_OBJ_DESTROY(ptr) specula::prof::event_object_destroy(ptr);
#define PROF_OBJ_SNAPSHOT(obj, ...)                                            \
  specula::prof::event_obj_snapshot(                                           \
      obj, SPECULA_PROF_FOREACH(SPECULA_KEY_VAL, obj, __VA_ARGS__));

#define PROF_STREAM_FILE(file) specula::prof::open_stream_file(file);
#define PROF_CLOSE_STREAM() specula::prof::close_stream_file();
#else
#define PROF_SCOPED(...)
#define PROF_FUNC(...)
#define PROF_FUNC_ARGS(...)
#define PROF_BEGIN(...)
#define PROF_END(...)
#define PROF_INST(...)
#define PROF_COUNTER(...)
#define PROF_COUNT(...)

#define PROF_OBJ(type)
#define PROF_OBJ_CONSTRUCT(ptr)
#define PROF_OBJ_DESTROY(ptr)
#define PROF_OBJ_SNAPSHOT(obj, ...)
#define PROF_STREAM_FILE(file)
#define PROF_CLOSE_STREAM()
#endif // __PROFILER__

namespace specula {
namespace prof {
enum EventType : char {
  BEGIN = 'B',
  END = 'E',
  INSTANCE = 'I',
  COUNTER = 'C',
  OBJECT_CONSTRUCT = 'N',
  OBJECT_DESTROY = 'D',
  OBJECT_SNAPSHOT = 'O',
};
struct Event {
  EventType type;
  const std::string name, cat, args;
  const std::size_t tid, id;
};

extern std::hash<std::thread::id> thread_hasher;
extern std::hash<const void *> pointer_hasher;
extern FILE *file_stream;

#ifdef __PROFILER__
inline void open_stream_file(const char *file) {
  file_stream = std::fopen(file, "w");
  std::fprintf(file_stream, "[");
}
inline void close_stream_file() {
  if (file_stream)
    std::fclose(file_stream);
}

inline void handle_event(const Event &event) {
  if (!file_stream)
    open_stream_file("profile.json");
  fmt::print(
      file_stream, "{{{}{}\"ph\":\"{}\",\"ts\":{},\"pid\":1,\"tid\":{}{}{}}},",
      (event.name.size() == 0) ? ""
                               : fmt::format("\"name\": \"{}\",", event.name),
      (event.cat.size() == 0) ? "" : fmt::format("\"cat\": \"{}\",", event.cat),
      event.type,
      std::chrono::duration_cast<std::chrono::microseconds>(
          std::chrono::high_resolution_clock::now().time_since_epoch())
          .count(),
      event.tid,
      (event.id == 0) ? "" : fmt::format(",\"id\":\"0x{:X}\"", event.id),
      (event.args.size() == 0) ? ""
                               : fmt::format(",\"args\":{{{}}}", event.args));
}

template <typename T> inline std::string fmt_type(const T &v) {
  return fmt::format("{}", v);
}
template <> inline std::string fmt_type(const std::string &v) {
  return fmt::format("\"{}\"", v);
}
template <typename T> inline std::string fmt_type(const std::vector<T> &v) {
  std::string res = "[";
  for (auto &it : v) {
    res += fmt_type(it) + ',';
  }
  return res.substr(0, v.size() != 0 ? res.size() - 1 : res.size()) + ']';
}
inline std::string fmt_args() { return ""; }
template <typename T>
inline std::string fmt_args(const std::string &key, const T &v) {
  return fmt::format("\"{}\": {}", key, fmt_type(v));
}
template <typename T, typename... Args>
inline std::string fmt_args(const std::string &key, const T &v,
                            const Args &... args) {
  return fmt::format("{}, \"{}\": {}", fmt_args(args...), key, fmt_type(v));
}

inline std::pair<std::string, std::string> split_cat_args() {
  return std::make_pair("", "");
}
template <typename... Args>
inline typename std::enable_if<(sizeof...(Args)) % 2 == 0,
                               std::pair<std::string, std::string>>::type
split_cat_args(const std::string &cat, const Args &... args) {
  return std::make_pair(cat, fmt_args(args...));
}
template <typename... Args>
inline typename std::enable_if<(sizeof...(Args)) % 2 != 0,
                               std::pair<std::string, std::string>>::type
split_cat_args(const std::string &cat, const Args &... args) {
  return std::make_pair("", fmt_args(cat, args...));
}

template <typename... Args>
inline void event_begin(const std::string &name, const Args &... args) {
  std::pair<std::string, std::string> cat_args = split_cat_args(args...);
  Event e{EventType::BEGIN,
          name,
          cat_args.first,
          cat_args.second,
          thread_hasher(std::this_thread::get_id()),
          0};
  handle_event(e);
}
template <typename... Args> inline void event_end(const Args &... args) {
  std::pair<std::string, std::string> cat_args = split_cat_args(args...);
  Event e{EventType::END,
          "",
          "",
          cat_args.second,
          thread_hasher(std::this_thread::get_id()),
          0};
  handle_event(e);
}
template <typename... Args>
inline void event_counter(const std::string &name, const Args &... args) {
  std::pair<std::string, std::string> cat_args = split_cat_args(args...);
  Event e{EventType::COUNTER,
          name,
          cat_args.first,
          cat_args.second,
          thread_hasher(std::this_thread::get_id()),
          0};
  handle_event(e);
}
template <typename T> inline void event_object_construct(const T *obj) {
  std::string type_str = typeid(&obj).name();
  type_str.substr(type_str.find_first_not_of(
      "0123456789", type_str.find_first_of("01234567789")));
  Event e{EventType::OBJECT_CONSTRUCT,
          type_str,
          "",
          "",
          thread_hasher(std::this_thread::get_id()),
          pointer_hasher(reinterpret_cast<const void *>(obj))};
  handle_event(e);
}
template <typename T> inline void event_object_destroy(const T *obj) {
  std::string type_str = typeid(&obj).name();
  type_str.substr(type_str.find_first_not_of(
      "0123456789", type_str.find_first_of("01234567789")));
  Event e{EventType::OBJECT_DESTROY,
          type_str,
          "",
          "",
          thread_hasher(std::this_thread::get_id()),
          pointer_hasher(reinterpret_cast<const void *>(obj))};
  handle_event(e);
}
template <typename T, typename... Args>
inline void event_object_snapshot(const T *obj, const Args &... args) {
  std::string type_str = typeid(&obj).name();
  type_str.substr(type_str.find_first_not_of(
      "0123456789", type_str.find_first_of("01234567789")));
  Event e{EventType::OBJECT_SNAPSHOT,
          type_str,
          "",
          fmt::format("\"snapshot\": {{{}}}", fmt_args(args...)),
          thread_hasher(std::this_thread::get_id()),
          pointer_hasher(reinterpret_cast<const void *>(obj))};
  handle_event(e);
}

struct ScopedProfiler {
  template <typename... Args>
  ScopedProfiler(const std::string &name, const Args &... args) {
    specula::prof::event_begin(name, args...);
  }
  ~ScopedProfiler() { specula::prof::event_end(); }
};
template <typename T> struct ObjectProfiler {
  ObjectProfiler(const T *ptr) : ptr(ptr) { prof::event_object_construct(ptr); }
  ~ObjectProfiler() { prof::event_object_destroy(ptr); }

private:
  const T *ptr;
};
#endif // __PROFILER__

} // namespace prof
} // namespace specula

#endif /* end of include guard: SPECULA_DEV_PROF_HPP_ */
