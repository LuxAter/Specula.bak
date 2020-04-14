#include "specula/core/memory.hpp"

void *specula::alloc_aligned(size_t size) {
#if SPECULA_OS_IS_Windows == 1
  return _aligned_malloc(size, SPECULA_L1_CACHE_LINE_SIZE);
#elif SPECULA_OS_IS_BSD == 1 || SPECULA_OS_IS_OSX == 1
  void *ptr;
  if (posix_memalign(&ptr, SPECULA_L1_CACHE_LINE_SIZE, size) != 0)
    ptr = nullptr;
  return ptr;
#else
  return memalign(SPECULA_L1_CACHE_LINE_SIZE, size);
#endif
}

void specula::free_aligned(void *ptr) {
  if (ptr == nullptr) {
    return;
  }
#if SPECULA_OS_IS_Windows == 1
  _aligned_free(ptr);
#else
  free(ptr);
#endif
}
