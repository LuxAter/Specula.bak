#ifndef SPECULA_PROF_HPP_
#define SPECULA_PROF_HPP_

#include <chrono>
#include <stack>
#include <thread>
#include <unordered_map>
#include <vector>

namespace specula {
namespace prof {
struct profile_data {
  profile_data(const std::string& name, const std::string& catagory,
               const std::uint32_t& color, const std::uint32_t& tid)
      : name(name), catagory(catagory), color(color), tid(tid), time_points(),
        children() {}
  profile_data(const std::string& name, const std::string& catagory,
               const std::uint32_t& color, const std::uint32_t& tid,
               const std::chrono::high_resolution_clock::time_point& tp)
      : name(name), catagory(catagory), color(color), tid(tid),
        time_points({tp}), children() {}
  const std::string name;
  const std::string catagory;
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

inline void push_scope(const std::string& name,
                       std::string catagory = std::string(),
                       std::uint32_t color = 0xFFFFFF) {
  const std::thread::id tid = std::this_thread::get_id();
  const std::size_t key_hash =
      key_hasher(name + catagory + std::to_string(color));
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
                              name, catagory, color, thread_hasher(tid),
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
void print_profile_data(const std::shared_ptr<profile_data>&,
                        std::size_t indent = 0, bool formatting = true);
void print_report(bool formatting = true);
} // namespace prof
} // namespace specula

#endif // SPECULA_PROF_HPP_
