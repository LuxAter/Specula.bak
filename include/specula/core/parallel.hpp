#ifndef SPECULA_CORE_PARALLEL_HPP_
#define SPECULA_CORE_PARALLEL_HPP_

#include "geometry.hpp"
#include "specula/global.hpp"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>

namespace specula {

extern SPECULA_THREAD_LOCAL int thread_index;

class AtomicFloat {
public:
  explicit AtomicFloat(Float v = 0) { bits = float_to_bits(v); }
  operator Float() const { return bits_to_float(bits); }
  Float operator=(Float v) {
    bits = float_to_bits(v);
    return v;
  }
  void add(Float v) {
#ifdef SPECULA_DOUBLE_PRECISION
    uint64_t old_bits = bits, new_bits;
#else
    uint32_t old_bits = bits, new_bits;
#endif
    do {
      new_bits = float_to_bits(bits_to_float(old_bits) + v);
    } while (!bits.compare_exchange_weak(old_bits, new_bits));
  }

private:
#ifdef SPECULA_DOUBLE_PRECISION
  std::atomic<uint64_t> bits;
#else
  std::atomic<uint32_t> bits;
#endif
};

class Barrier {
public:
  Barrier(int count) : count(count) { CHECK_GT(count, 0); }
  ~Barrier() { CHECK_EQ(count, 0); }
  void wait();

private:
  std::mutex mutex;
  std::condition_variable cv;
  int count;
};

void parallel_for(const std::function<void(int64_t)> &func, int64_t count,
                  int chunk_size = 1);
void parallel_for(const std::function<void(Point2i)> &func,
                     const Point2i &count);
int max_thread_index();
int num_system_cores();

void parallel_init();
void parallel_cleanup();
void merge_worker_thread_stats();
} // namespace specula

#endif // SPECULA_CORE_PARALLEL_HPP_
