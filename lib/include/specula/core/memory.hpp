#ifndef SPECULA_CORE_MEMORY_HPP
#define SPECULA_CORE_MEMORY_HPP

#include "specula/global.hpp"

#include <cstddef>
#include <list>

#ifndef SPECULA_L1_CACHE_LINE_SIZE
#define SPECULA_L1_CACHE_LINE_SIZE 64
#endif

namespace specula {
// TODO Consider using aligned_alloc or (std::aligned_alloc C++17)
void *alloc_aligned(size_t size);
void free_aligned(void *);

template <typename T> T *alloc_aligned(size_t count) {
  return reinterpret_cast<T *>(alloc_aligned(count * sizeof(T)));
}

class SPECULA_ALIGNAS(SPECULA_L1_CACHE_LINE_SIZE) MemoryArena {
public:
  MemoryArena(size_t block_size = 262144) : block_size(block_size) {}
  ~MemoryArena() {
    free_aligned(current_block);
    for (auto &block : used_blocks)
      free_aligned(block.second);
    for (auto &block : available_blocks)
      free_aligned(block.second);
  }

  void *alloc(size_t bytes) {
    const size_t align = SPECULA_ALIGNOF(std::max_align_t);
    SPECULA_STATIC_ASSERT_MSG(is_power_of_2(align),
                              "Minimum alignment not a power of two");
    bytes = (bytes + align - 1) & ~(align - 1);
    if (current_block_pos + bytes > current_alloc_size) {
      if (current_block) {
        used_blocks.push_back(
            std::make_pair(current_alloc_size, current_block));
        current_block = nullptr;
        current_alloc_size = 0;
      }
      for (auto iter = available_blocks.begin(); iter != available_blocks.end();
           ++iter) {
        if (iter->first >= bytes) {
          current_alloc_size = iter->first;
          current_block = iter->second;
          available_blocks.erase(iter);
          break;
        }
      }
      if (!current_block) {
        current_alloc_size = std::max(bytes, block_size);
        current_block = alloc_aligned<uint8_t>(current_alloc_size);
      }
      current_block_pos = 0;
    }
    void *ret = current_block + current_block_pos;
    current_block_pos += bytes;
    return ret;
  }
  template <typename T> T *alloc(size_t n = 1, bool constructor = true) {
    T *ret = reinterpret_cast<T *>(n * sizeof(T));
    if (constructor) {
      for (size_t i = 0; i < n; ++i)
        new (&ret[i]) T();
    }
    return ret;
  }
  void reset() {
    current_block_pos = 0;
    available_blocks.splice(available_blocks.begin(), used_blocks);
  }
  size_t total_allocated() const {
    size_t total = current_alloc_size;
    for (const auto &block : used_blocks)
      total += block.first;
    for (const auto &block : available_blocks)
      total += block.first;
    return total;
  }

private:
  MemoryArena(const MemoryArena &) SPECULA_DELETED_FUNCTION;
  MemoryArena &operator=(const MemoryArena &) SPECULA_DELETED_FUNCTION;

  const size_t block_size;
  size_t current_block_pos = 0, current_alloc_size = 0;
  uint8_t *current_block = nullptr;
  std::list<std::pair<size_t, uint8_t *>> used_blocks, available_blocks;
};

template <typename T, size_t LogBlockSize> class BlockedArray {
public:
  BlockedArray(size_t u_res, size_t v_res, const T *d = nullptr)
      : u_res(u_res), v_res(v_res), u_blocks(round_up(u_res) >> LogBlockSize) {
    size_t n_alloc = round_up(u_res) * round_up(v_res);
    data = alloc_aligned<T>(n_alloc);
    for (size_t i = 0; i < n_alloc; ++i)
      new (&data[i]) T();
    if (d) {
      for (size_t v = 0; v < v_res; ++v) {
        for (size_t u = 0; u < u_res; ++u) {
          (*this)(u, v) = data[v * u_res + u];
        }
      }
    }
  }

  ~BlockedArray() {
    for (size_t i = 0; i < u_res * v_res; ++i)
      data[i].~T();
    free_aligned(data);
  }

  SPECULA_CONSTEXPR size_t block_size() const { return 1 << LogBlockSize; }
  size_t u_size() const { return u_res; }
  size_t v_size() const { return v_res; }

  size_t round_up(size_t x) const {
    return (x + block_size() - 1) & ~(block_size() - 1);
  }
  size_t block(size_t a) const { return a >> LogBlockSize; }
  size_t offset(size_t a) const { return (a & (block_size() - 1)); }
  T &operator()(size_t u, size_t v) {
    size_t bu = block(u), bv = block(v);
    size_t ou = offset(u), ov = offset(v);
    size_t offset = block_size() * block_size() * (u_blocks * bv + bu);
    offset += block_size() * ov + ou;
    return data[offset];
  }
  const T &operator()(size_t u, size_t v) const {
    size_t bu = block(u), bv = block(v);
    size_t ou = offset(u), ov = offset(v);
    size_t offset = block_size() * block_size() * (u_blocks * bv + bu);
    offset += block_size() * ov + ou;
    return data[offset];
  }
  void get_linear_array(T *a) const {
    for (size_t v = 0; v < v_res; ++v) {
      for (size_t u = 0; u < u_res; ++u) {
        *a++ = (*this)(u, v);
      }
    }
  }

private:
  T *data;
  const size_t u_res, v_res, u_blocks;
};
} // namespace specula

#endif /* end of include guard: SPECULA_CORE_MEMORY_HPP */
