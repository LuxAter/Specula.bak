#include "specula/dev/prof.hpp"

#include <cstdio>
#include <thread>

namespace specula {
namespace prof {
std::hash<std::thread::id> thread_hasher;
std::hash<const void *> pointer_hasher;
FILE *file_stream = nullptr;
} // namespace prof
} // namespace specula
