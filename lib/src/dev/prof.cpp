#include "specula/dev/prof.hpp"

#include <cstdio>
#include <thread>

namespace specula::prof {
std::hash<std::thread::id> thread_hasher;
std::hash<const void *> pointer_hasher;
std::mutex mutex;
FILE *file_stream = nullptr;
} // namespace specula::prof
