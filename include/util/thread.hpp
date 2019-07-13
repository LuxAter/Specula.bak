#ifndef SPECULA_UTIL_THREAD_HPP_
#define SPECULA_UTIL_THREAD_HPP_

#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

#include "log.hpp"

namespace specula {
namespace thread {
template <class _Return, class... _Args> class Queue {
public:
  explicit Queue(std::size_t threads = std::thread::hardware_concurrency())
      : threads_(threads) {
    if (threads_ == 0)
      threads_ = 1;
  }
  Queue(_Return (*func)(_Args...),
        std::size_t threads = std::thread::hardware_concurrency())
      : threads_(threads), func_(func) {
    if (threads_ == 0)
      threads_ = 1;
  }

  ~Queue() {
    for (std::size_t i = 0; i < pool_.size(); ++i) {
      pool_[i].wait();
    }
  }

  void push(_Args... args) {
    if (pool_.size() == threads_) {
      return_values_.push(pool_.front().get());
      pool_.erase(pool_.begin());
    }
    pool_.push_back(std::async(func_, args...));
  }

  _Return get() {
    _Return res;
    if (return_values_.size() == 0 && pool_.size() != 0) {
      res = pool_.front().get();
      pool_.erase(pool_.begin());
    } else if (return_values_.size() != 0) {
      res = return_values_.front();
      return_values_.pop();
    }
    return res;
  }

  void wait() {
    for (std::size_t i = 0; i < pool_.size(); ++i) {
      return_values_.push(pool_[i].get());
    }
    pool_.clear();
  }

  void clear() { return_values_.clear(); }

  inline std::size_t size() const { return threads_; }

private:
  std::size_t threads_;
  std::vector<std::future<_Return>> pool_;
  _Return (*func_)(_Args...) = NULL;
  std::queue<_Return> return_values_;
}; // namespace thread
} // namespace thread
} // namespace specula

#endif // SPECULA_UTIL_THREAD_HPP_
