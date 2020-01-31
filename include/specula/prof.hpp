#ifndef SPECULA_PROF_HPP_
#define SPECULA_PROF_HPP_

#include <chrono>
#include <stack>
#include <thread>
#include <unordered_map>
#include <vector>
#include <exception>

#define PROF_STRINGIFY_IMPL(x) #x
#define PROF_STRINGIFY(x) PROF_STRINGIFY_IMPL(x)
#define PROF_CONCAT4_IMPL(a, b, c, d) a##b##c##d
#define PROF_CONCAT4(a, b, c, d) PROF_CONCAT4_IMPL(a, b, c, d)
#define PROF_SCOPE_NAME                                                        \
  PROF_CONCAT4(__profiler_scoped_, __LINE__, _, __COUNTER__)
#define PROF_SCOPE_NAME_STR PROF_STRINGIFY(PROF_SCOPE_NAME)
#define PROF_FUNCTION __PRETTY_FUNCTION__

#define PROF_GET_3TH_ARGS(arg1, arg2, arg3, ...) arg3

#define PROF_FUNC_0(...)                                                       \
  specula::prof::scoped_profiler PROF_SCOPE_NAME =                             \
      specula::prof::scoped_profiler(PROF_FUNCTION);
#define PROF_FUNC_1(a, ...)                                                    \
  specula::prof::scoped_profiler PROF_SCOPE_NAME =                             \
      specula::prof::scoped_profiler(PROF_FUNCTION, a);
#define PROF_FUNC_2(a, b, ...)                                                 \
  specula::prof::scoped_profiler PROF_SCOPE_NAME =                             \
      specula::prof::scoped_profiler(PROF_FUNCTION, a, b);

#define PROF_FUNC_SELECT(x, A, B, FUNC, ...) FUNC

#define PROF_FUNC(...)                                                         \
  PROF_FUNC_SELECT(__VA_ARGS__, PROF_FUNC_2, PROF_FUNC_1, PROF_FUNC_0)         \
  (__VA_ARGS__)
#define PROF_SCOPED(...)                                                       \
  specula::prof::scoped_profiler PROF_SCOPE_NAME =                             \
      specula::prof::scoped_profiler(__VA_ARGS__);
#define PROF_BEGIN(...) specula::prof::push_scope(__VA_ARGS__);
#define PROF_END() specula::prof::pop_scope();

#define PROF_WRITE(file) specula::prof::write_to_file(file);
#define PROF_DUMP(file) specula::prof::dump_to_file(file);
// #define PROF_FUNC(...)
// #define PROF_SCOPED(...)
// #define PROF_BEGIN(...)
// #define PROF_END()

namespace specula {
namespace prof {
struct profile_data {
  profile_data(const std::string& name, const std::string& category,
               const std::uint32_t& color, const std::uint32_t& tid)
      : name(name), category(category), color(color), tid(tid), time_points(),
        children() {}
  profile_data(const std::string& name, const std::string& category,
               const std::uint32_t& color, const std::uint32_t& tid,
               const std::chrono::high_resolution_clock::time_point& tp)
      : name(name), category(category), color(color), tid(tid),
        time_points({tp}), children() {}
  const std::string name;
  const std::string category;
  const std::uint32_t color;
  const std::uint32_t tid;
  std::vector<std::chrono::high_resolution_clock::time_point> time_points;
  std::unordered_map<std::size_t, std::shared_ptr<profile_data>> children;
};
extern std::unordered_map<std::thread::id,
                          std::stack<std::shared_ptr<profile_data>>>
    profile_stack;
extern std::unordered_map<
    std::thread::id,
    std::unordered_map<std::size_t, std::shared_ptr<profile_data>>>
    profile_store;
extern std::hash<std::thread::id> thread_hasher;
extern std::hash<std::string> key_hasher;

inline void push_scope(const std::string& name, std::uint32_t color,
                       std::string category = std::string()) {
  const std::thread::id tid = std::this_thread::get_id();
  const std::size_t key_hash =
      key_hasher(name + category + std::to_string(color));
  std::unordered_map<std::size_t, std::shared_ptr<profile_data>>* data_ptr =
      nullptr;

  std::unordered_map<
      std::thread::id,
      std::unordered_map<std::size_t, std::shared_ptr<profile_data>>>::iterator
      store_iter;
  std::unordered_map<std::thread::id,
                     std::stack<std::shared_ptr<profile_data>>>::iterator
      stack_iter = profile_stack.find(tid);
  if (stack_iter != profile_stack.end() && !stack_iter->second.empty()) {
    data_ptr = &(stack_iter->second.top()->children);
  } else if ((store_iter = profile_store.find(tid)) != profile_store.end()) {
    data_ptr = &(store_iter->second);
  } else {
    data_ptr =
        &(profile_store
              .insert(std::make_pair(
                  tid, std::unordered_map<std::size_t,
                                          std::shared_ptr<profile_data>>()))
              .first->second);
  }

  std::unordered_map<std::size_t, std::shared_ptr<profile_data>>::iterator
      data_iter = data_ptr->find(key_hash);
  if (data_iter != data_ptr->end()) {
    if (data_iter->second->time_points.size() % 2 != 0)
      throw std::logic_error("Pushing to profiler that is already active");
    data_iter->second->time_points.push_back(
        std::chrono::high_resolution_clock::now());
  } else {
    data_iter =
        data_ptr
            ->insert(std::make_pair(
                key_hash, std::make_shared<profile_data>(
                              name, category, color, thread_hasher(tid),
                              std::chrono::high_resolution_clock::now())))
            .first;
  }
  if (stack_iter != profile_stack.end()) {
    stack_iter->second.push(data_iter->second);
  } else {
    stack_iter = profile_stack
                     .insert(std::make_pair(
                         tid, std::stack<std::shared_ptr<profile_data>>()))
                     .first;
    stack_iter->second.push(data_iter->second);
  }
}
inline void push_scope(const std::string& name,
                       std::string category = std::string(),
                       std::uint32_t color = 0xFFFFFF) {
  const std::thread::id tid = std::this_thread::get_id();
  const std::size_t key_hash =
      key_hasher(name + category + std::to_string(color));
  std::unordered_map<std::size_t, std::shared_ptr<profile_data>>* data_ptr =
      nullptr;

  std::unordered_map<
      std::thread::id,
      std::unordered_map<std::size_t, std::shared_ptr<profile_data>>>::iterator
      store_iter;
  std::unordered_map<std::thread::id,
                     std::stack<std::shared_ptr<profile_data>>>::iterator
      stack_iter = profile_stack.find(tid);
  if (stack_iter != profile_stack.end() && !stack_iter->second.empty()) {
    data_ptr = &(stack_iter->second.top()->children);
  } else if ((store_iter = profile_store.find(tid)) != profile_store.end()) {
    data_ptr = &(store_iter->second);
  } else {
    data_ptr =
        &(profile_store
              .insert(std::make_pair(
                  tid, std::unordered_map<std::size_t,
                                          std::shared_ptr<profile_data>>()))
              .first->second);
  }

  std::unordered_map<std::size_t, std::shared_ptr<profile_data>>::iterator
      data_iter = data_ptr->find(key_hash);
  if (data_iter != data_ptr->end()) {
    if (data_iter->second->time_points.size() % 2 != 0)
      throw std::logic_error("Pushing to profiler that is already active");
    data_iter->second->time_points.push_back(
        std::chrono::high_resolution_clock::now());
  } else {
    data_iter =
        data_ptr
            ->insert(std::make_pair(
                key_hash, std::make_shared<profile_data>(
                              name, category, color, thread_hasher(tid),
                              std::chrono::high_resolution_clock::now())))
            .first;
  }
  if (stack_iter != profile_stack.end()) {
    stack_iter->second.push(data_iter->second);
  } else {
    stack_iter = profile_stack
                     .insert(std::make_pair(
                         tid, std::stack<std::shared_ptr<profile_data>>()))
                     .first;
    stack_iter->second.push(data_iter->second);
  }
}
inline void pop_scope() {
  std::unordered_map<std::thread::id,
                     std::stack<std::shared_ptr<profile_data>>>::iterator
      stack_iter = profile_stack.find(std::this_thread::get_id());
  if (stack_iter == profile_stack.end())
    throw std::logic_error("Poping profiler from unprofiled thread");
  if (stack_iter->second.empty())
    throw std::logic_error("Poping from thread with no active profiler");
  stack_iter->second.top()->time_points.push_back(
      std::chrono::high_resolution_clock::now());
  stack_iter->second.pop();
}

void dump_to_file(const std::string& file);
void dump_to_txt(const std::string& file);
void dump_to_csv(const std::string& file);
void dump_to_json(const std::string& file);
void write_to_file(const std::string& file);
void write_to_txt(const std::string& file);
void write_to_csv(const std::string& file);
void write_to_json(const std::string& file);
void write_profile_data_txt(FILE* out, const std::shared_ptr<profile_data>& data);
void write_profile_data_csv(FILE* out, const std::shared_ptr<profile_data>& data);
void write_profile_data_json(FILE* out, const std::shared_ptr<profile_data>& data);

void print_profile_data(const std::shared_ptr<profile_data>&,
                        std::size_t indent = 0, bool formatting = true);
void print_report(bool formatting = true);

struct scoped_profiler {
  scoped_profiler(const std::string& name, std::string category = std::string(),
                  std::uint32_t color = 0xFFFFFF) {
    specula::prof::push_scope(name, category, color);
  }
  ~scoped_profiler() { specula::prof::pop_scope(); }
};

} // namespace prof
} // namespace specula

#endif // SPECULA_PROF_HPP_
