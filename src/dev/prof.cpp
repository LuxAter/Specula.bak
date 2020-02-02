#include "specula/dev/prof.hpp"

#include <cstdio>
#include <thread>

namespace specula {
namespace prof {
std::hash<std::thread::id> thread_hasher;
std::hash<const void*> pointer_hasher;
namespace fs {
FILE* file_stream = nullptr;
} // namespace fs
} // namespace prof
} // namespace specula

