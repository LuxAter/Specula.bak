#include "specula/core/parallel.hpp"

#include "core/geometry.hpp"
#include "global/compiler.hpp"
#include "global/functions.hpp"
#include "spdlog/spdlog.h"
#include "specula/global.hpp"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <mutex>
#include <thread>
#include <vector>

namespace specula {
class ParallelForLoop;

static std::vector<std::thread> threads;
static bool shutdown_threads = false;
static ParallelForLoop *work_list = nullptr;
static std::mutex work_list_mutex;
static std::atomic<bool> report_worker_stats{false};
static std::atomic<int> reporter_count;
static std::condition_variable report_done_condition;
static std::mutex report_done_mutex;
static std::condition_variable work_list_condition;
SPECULA_THREAD_LOCAL int thread_index;

class ParallelForLoop {
public:
  ParallelForLoop(const std::function<void(int64_t)> &func1D, int64_t max_index,
                  int chunk_size)
      : func1D(std::move(func1D)), max_index(max_index),
        chunk_size(chunk_size) {}
  ParallelForLoop(const std::function<void(Point2i)> &func2D,
                  const Point2i &count)
      : func2D(std::move(func2D)), max_index(count.x * count.y), chunk_size(1),
        nx(count.x) {}

  bool finished() const {
    return next_index >= max_index && active_worker == 0;
  }

  std::function<void(int64_t)> func1D;
  std::function<void(Point2i)> func2D;
  const int64_t max_index;
  const int chunk_size;
  int64_t next_index = 0;
  int active_worker = 0;
  ParallelForLoop *next = nullptr;
  int nx = -1;
};

static void worker_thread_func(int tindex, std::shared_ptr<Barrier> barrier) {
  LINFO("Started execution in worker thread {}", tindex);
  thread_index = tindex;
  barrier->wait();
  barrier.reset();
  std::unique_lock<std::mutex> lock(work_list_mutex);
  while (!shutdown_threads) {
    if (report_worker_stats) {
      if (--reporter_count == 0)
        report_done_condition.notify_one();
      work_list_condition.wait(lock);
    } else if (!work_list) {
      work_list_condition.wait(lock);
    } else {
      ParallelForLoop &loop = *work_list;
      int64_t index_start = loop.next_index;
      int64_t index_end =
          std::min(index_start + loop.chunk_size, loop.max_index);
      loop.next_index = index_end;
      if (loop.next_index == loop.max_index)
        work_list = loop.next;
      loop.active_worker++;

      lock.unlock();
      for (int64_t index = index_start; index < index_end; ++index) {
        if (loop.func1D) {
          loop.func1D(index);
        } else {
          CHECK(loop.func2D);
          loop.func2D(Point2i(index % loop.nx, index / loop.nx));
        }
      }
      lock.lock();
      loop.active_worker--;
      if (loop.finished())
        work_list_condition.notify_all();
    }
  }
  LINFO("Exiting worker thread {}", tindex);
}
} // namespace specula

void specula::Barrier::wait() {
  std::unique_lock<std::mutex> lock(mutex);
  CHECK_GT(count, 0);
  if (--count == 0)
    cv.notify_all();
  else
    cv.wait(lock, [this] { return count == 0; });
}

void specula::parallel_for(const std::function<void(int64_t)> &func,
                           int64_t count, int chunk_size) {
  CHECK(threads.size() > 0 || max_thread_index() == 1);
  if (threads.empty() || count < chunk_size) {
    for (int64_t i = 0; i < count; ++i)
      func(i);
    return;
  }
  ParallelForLoop loop(std::move(func), count, chunk_size);
  work_list_mutex.lock();
  work_list = &loop;
  work_list_mutex.unlock();
  std::unique_lock<std::mutex> lock(work_list_mutex);
  work_list_condition.notify_all();

  while (!loop.finished()) {
    int64_t index_start = loop.next_index;
    int64_t index_end = std::min(index_start + loop.chunk_size, loop.max_index);
    loop.next_index = index_end;
    if (loop.next_index == loop.max_index)
      work_list = loop.next;
    loop.active_worker++;

    lock.unlock();
    for (int64_t index = index_start; index < index_end; ++index) {
      loop.func1D(index);
    }
    lock.lock();
    loop.active_worker--;
  }
}
void specula::parallel_for(const std::function<void(Point2i)> &func,
                           const Point2i &count) {
  CHECK(threads.size() > 0 || max_thread_index() == 1);
  if (threads.empty() || count.x * count.y <= 1) {
    for (int y = 0; y < count.y; ++y) {
      for (int x = 0; x < count.x; ++x) {
        func(Point2i(x, y));
      }
    }
    return;
  }
  ParallelForLoop loop(std::move(func), count);
  {
    std::lock_guard<std::mutex> lock(work_list_mutex);
    loop.next = work_list;
    work_list = &loop;
  }
  std::unique_lock<std::mutex> lock(work_list_mutex);
  work_list_condition.notify_all();

  while (!loop.finished()) {
    int64_t index_start = loop.next_index;
    int64_t index_end = std::min(index_start + loop.chunk_size, loop.max_index);
    loop.next_index = index_end;
    if (loop.next_index == loop.max_index)
      work_list = loop.next;
    loop.active_worker++;

    lock.unlock();
    for (int64_t index = index_start; index < index_end; ++index) {
      loop.func2D(Point2i(index % loop.nx, index / loop.nx));
    }
    lock.lock();
    loop.active_worker--;
  }
}

// TODO: Add option to control maximum number of threads.
int specula::max_thread_index() { return num_system_cores(); }
int specula::num_system_cores() {
  return std::max(1u, std::thread::hardware_concurrency());
}

void specula::parallel_init() {
  CHECK_EQ(threads.size(), 0u);
  int nthreads = max_thread_index();
  thread_index = 0;

  std::shared_ptr<Barrier> barrier = std::make_shared<Barrier>(nthreads);
  for (int i = 0; i < nthreads - 1; ++i) {
    threads.push_back(std::thread(worker_thread_func, i + 1, barrier));
  }
  barrier->wait();
}
void specula::parallel_cleanup() {
  if (threads.empty())
    return;
  {
    std::lock_guard<std::mutex> lock(work_list_mutex);
    shutdown_threads = true;
    work_list_condition.notify_all();
  }
  for (std::thread &thread : threads)
    thread.join();
  threads.erase(threads.begin(), threads.end());
  shutdown_threads = false;
}
void specula::merge_worker_thread_stats() {
  std::unique_lock<std::mutex> lock(work_list_mutex);
  std::unique_lock<std::mutex> done_lock(report_done_mutex);
  report_worker_stats = true;
  reporter_count = threads.size();
  work_list_condition.notify_all();
  report_done_condition.wait(lock, []() { return reporter_count == 0; });
  report_worker_stats = false;
}
