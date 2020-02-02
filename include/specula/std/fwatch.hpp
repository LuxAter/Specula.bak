#ifndef SPECULA_FWATCH_HPP_
#define SPECULA_FWATCH_HPP_

#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "filesystem.hpp"

namespace specula {
namespace fs {
class WatchedFileSystemExc : public std::exception {
public:
  WatchedFileSystemExc(const fs::path& path);
  virtual const char* what() const throw();
  char message[4096];
};
class FileWatch {
public:
  ~FileWatch();
  static void watch(const fs::path& path,
                    const std::function<void(const fs::path&)>& callback);
  static void
  watch(const fs::path& path,
        const std::function<void(const std::vector<fs::path>&)>& callback);
  static void unwatch(const fs::path& path);
  static void unwatch_all();
  static void
  touch(const fs::path& path,
        fs::file_time_type time = fs::file_time_type::clock::now());

protected:
  class Watcher {
  public:
    Watcher();
    Watcher(
        const fs::path& path, const std::string& filter,
        const std::function<void(const fs::path&)>& callback,
        const std::function<void(const std::vector<fs::path>&)>& list_callback);
    void watch();
    bool has_changed(const fs::path& path);

  protected:
    fs::path path;
    std::string filter;
    std::function<void(const fs::path&)> callback;
    std::function<void(const std::vector<fs::path>&)> list_callback;
    std::unordered_map<std::size_t, fs::file_time_type> modification_times;
  };

  FileWatch();
  void close();
  void start();
  static void watch_impl(
      const fs::path& path,
      const std::function<void(const fs::path&)>& callback =
          std::function<void(const fs::path&)>(),
      const std::function<void(const std::vector<fs::path>&)> list_callback =
          std::function<void(const std::vector<fs::path>&)>());
  static std::pair<fs::path, std::string>
  get_path_filter_pair(const fs::path& path);
  static std::pair<fs::path, std::string>
  visit_wild_card_path(const fs::path& path,
                       const std::function<bool(const fs::path&)>& visitor);

  static std::hash<fs::path> path_hash;
  std::mutex mutex;
  std::atomic<bool> watching;
  std::unique_ptr<std::thread> thread;
  std::unordered_map<std::size_t, Watcher> file_watchers;
};
} // namespace fs
} // namespace specula

#endif // SPECULA_FWATCH_HPP_
