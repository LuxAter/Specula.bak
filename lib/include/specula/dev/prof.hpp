#ifndef SPECULA_DEV_PROF_HPP_
#define SPECULA_DEV_PROF_HPP_

#include <cstdio>
#include <mutex>
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

#define SPECULA_PROF_FUNC_KEY(val) #val, val
#define SPECULA_PROF_KEY_VAL(obj, key) #key, (obj)->key

#if SPECULA_COMPILER_IS_GNU == 1
#define SPECULA_PROF_FUNCTION_NAME __PRETTY_FUNCTION__
#elif SPECULA_COMPILER_IS_MSVC == 1
#define SPECULA_PROF_FUNCTION_NAME __FUNCSIG__
#else
#define SPECULA_PROF_FUNCTION_NAME __func__
#endif
#define SPECULA_PROFILER_NAME                                                  \
  SPECULA_PROF_CONCAT(__PROFILER_, __COUNTER__, _, __LINE__)

#define SPECULA_PROF_SCOPED_NAME                                               \
  SPECULA_PROF_CONCAT(__ProfilerScoped_, __LINE__, _, __COUNTER__)
#define SPECULA_PROF_SCOPED_NAME_STR                                           \
  SPECULA_PROF_STRINGIFY(SPECULA_PROF_SCOPED_NAME)
#define SPECULA_PROF_FUNCTION __PRETTY_FUNCTION__

#define FUNC_OBJ(FUNC, obj, x) FUNC(obj, x);
#define FUNC_NO_OBJ(FUNC, obj, x) FUNC(x);
#define FUNC_OBJ_LIST(FUNC, obj, x) , FUNC(obj, x)
#define FUNC_NO_OBJ_LIST(FUNC, obj, x) , FUNC(x)

#define EVAL0(CALLER, FUNC, obj, ...)
#define EVAL1(CALLER, FUNC, obj, x, ...) CALLER(FUNC, obj, x)
#define EVAL2(CALLER, FUNC, obj, x, ...)                                       \
  CALLER(FUNC, obj, x) EVAL1(CALLER, FUNC, obj, __VA_ARGS__)
#define EVAL3(CALLER, FUNC, obj, x, ...)                                       \
  CALLER(FUNC, obj, x) EVAL2(CALLER, FUNC, obj, __VA_ARGS__)
#define EVAL4(CALLER, FUNC, obj, x, ...)                                       \
  CALLER(FUNC, obj, x) EVAL3(CALLER, FUNC, obj, __VA_ARGS__)
#define EVAL5(CALLER, FUNC, obj, x, ...)                                       \
  CALLER(FUNC, obj, x) EVAL4(CALLER, FUNC, obj, __VA_ARGS__)
#define EVAL6(CALLER, FUNC, obj, x, ...)                                       \
  CALLER(FUNC, obj, x) EVAL5(CALLER, FUNC, obj, __VA_ARGS__)
#define EVAL7(CALLER, FUNC, obj, x, ...)                                       \
  CALLER(FUNC, obj, x) EVAL6(CALLER, FUNC, obj, __VA_ARGS__)
#define EVAL8(CALLER, FUNC, obj, x, ...)                                       \
  CALLER(FUNC, obj, x) EVAL7(CALLER, FUNC, obj, __VA_ARGS__)
#define EVAL9(CALLER, FUNC, obj, x, ...)                                       \
  CALLER(FUNC, obj, x) EVAL8(CALLER, FUNC, obj, __VA_ARGS__)
#define EVAL10(CALLER, FUNC, obj, x, ...)                                      \
  CALLER(FUNC, obj, x) EVAL9(CALLER, FUNC, obj, __VA_ARGS__)

#define GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME

#define FOR_EACH(FUNC, ...)                                                    \
  GET_MACRO(_0 __VA_OPT__(, ) __VA_ARGS__, EVAL10, EVAL9, EVAL8, EVAL7, EVAL6, \
            EVAL5, EVAL4, EVAL3, EVAL2, EVAL1, EVAL0)                          \
  (FUNC_NO_OBJ, FUNC, _0, __VA_ARGS__)
#define FOR_EACH_OBJ(FUNC, obj, ...)                                           \
  GET_MACRO(_0 __VA_OPT__(, ) __VA_ARGS__, EVAL10, EVAL9, EVAL8, EVAL7, EVAL6, \
            EVAL5, EVAL4, EVAL3, EVAL2, EVAL1, EVAL0)                          \
  (FUNC_OBJ, FUNC, obj, __VA_ARGS__)
#define FOR_EACH_LIST(FUNC, ...)                                               \
  GET_MACRO(_0 __VA_OPT__(, ) __VA_ARGS__, EVAL10, EVAL9, EVAL8, EVAL7, EVAL6, \
            EVAL5, EVAL4, EVAL3, EVAL2, EVAL1, EVAL0)                          \
  (FUNC_NO_OBJ_LIST, FUNC, _0, __VA_ARGS__)
#define FOR_EACH_OBJ_LIST(FUNC, obj, ...)                                      \
  GET_MACRO(_0 __VA_OPT__(, ) __VA_ARGS__, EVAL10, EVAL9, EVAL8, EVAL7, EVAL6, \
            EVAL5, EVAL4, EVAL3, EVAL2, EVAL1, EVAL0)                          \
  (FUNC_OBJ_LIST, FUNC, obj, __VA_ARGS__)

#define PROF_SCOPED(...)                                                       \
  specula::prof::ScopedProfiler SPECULA_PROF_SCOPED_NAME =                     \
      specula::prof::ScopedProfiler(__VA_ARGS__);
#define PROF_FUNC(...)                                                         \
  specula::prof::ScopedProfiler SPECULA_PROF_SCOPED_NAME =                     \
      specula::prof::ScopedProfiler(SPECULA_PROF_FUNCTION);
#define PROF_FUNC_CAT(cat, ...)                                                \
  specula::prof::ScopedProfiler SPECULA_PROF_SCOPED_NAME =                     \
      specula::prof::ScopedProfiler(SPECULA_PROF_FUNCTION, cat);
#define PROF_FUNC_ARGS(...)                                                    \
  specula::prof::ScopedProfiler SPECULA_PROF_SCOPED_NAME =                     \
      specula::prof::ScopedProfiler(SPECULA_PROF_FUNCTION FOR_EACH_LIST(       \
          SPECULA_PROF_FUNC_KEY, __VA_ARGS__));
#define PROF_FUNC_CAT_ARGS(cat, ...)                                           \
  specula::prof::ScopedProfiler SPECULA_PROF_SCOPED_NAME =                     \
      specula::prof::ScopedProfiler(                                           \
          SPECULA_PROF_FUNCTION,                                               \
          cat FOR_EACH_LIST(SPECULA_PROF_FUNC_KEY, __VA_ARGS__));

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
      obj FOR_EACH_OBJ_LIST(SPECULA_KEY_VAL, obj, __VA_ARGS__));

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
extern std::mutex mutex;
extern FILE *file_stream;

#ifdef __PROFILER__
inline void open_stream_file(const char *file) {
  std::lock_guard<std::mutex> lock(mutex);
  file_stream = std::fopen(file, "w");
  std::fprintf(file_stream, "[");
}
inline void close_stream_file() {
  std::lock_guard<std::mutex> lock(mutex);
  if (file_stream)
    std::fclose(file_stream);
}

inline void handle_event(const Event &event) {
  if (!file_stream)
    open_stream_file("profile.json");
  std::lock_guard<std::mutex> lock(mutex);
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
