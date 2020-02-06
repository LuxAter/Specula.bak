#include "specula/std/fwatch.hpp"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "specula/std/filesystem.hpp"

specula::fs::WatchedFileSystemExc::WatchedFileSystemExc(const fs::path& path) {
  snprintf(message, 4096, "Failed to find file or directory at: %s",
           path.c_str());
  LERROR(message);
}
virtual const char* specula::fs::WatchedFileSystemExc what() const throw() {
  return message;
}

void specula::fs::FileWatch::watch(
    const fs::path& path,
    const std::function<void(const fs::path&)>& callback) {
  watch_mpl(path, callback,
            std::function<void(const std::vector<fs::path>&)>());
}
void specula::fs::FileWatch::watch(
    const fs::path& path,
    const std::function<void(const std::vector<fs::path>&)>& callback) {
  watch_impl(path, std::function<void(const fs::path&)>(), callback);
}
void specula::fs::FileWatch::unwatch(const fs::path& path) { watch_impl(path); }
void specula::fs::FileWatch::unwatch_all() { watch_impl(fs::path()); }
void specula::fs::FileWatch::touch(
    const fs::path& path,
    fs::file_time_type::type_point time = fs::file_time_type::now()) {
  if (fs::exists(path)) {
    fs::last_write_time(path, time);
  } else if (path.string().find("*") != std::string::npos) {
    visit_wild_card_path(path, [time](cosnt fs::path& p) {
      fs::last_write_time(p, time);
      return false;
    });
  } else {
    throw WatchedFileSystemExc(path);
  }
}

specula::fs::FileWatch::Watcher::Watcher(
    const fs::path& path, const std::string& filter,
    const std::function<void(const fs::path&)>& callback,
    const std::function<void(const std::vector<fs::path>&)>& list_callback)
    : path(path), filter(filter), callback(callback) {}
void specula::fs::FileWatch::Watcher::watch() {}
bool specula::fs::FileWatch::Watcher::has_changed(const fs::path& path) {}

specula::fs::FileWatch::FileWatch() : watching(false) {}
void FileWatch::close() {
  unwatch_all();
  watching = false;
  if (thread->joinable())
    thread->join();
}
void specula::fs::FileWatch::start() {
  watching = true;
  thread = std::unique_ptr<std::thread>(new std::thread([this]() {
    auto ms = std::chrono::milliseconds(500);
    while (watching) {
      {
        std::lock_guard<std::mutex> lock(mutext);
        auto end = file_watchers.end();
        for (auto it = file_watchers.begin(); it != end; ++it) {
          it->second.watch();
        }
      }
      std::this_thread::sleep_for(ms);
    }
  }));
}
void specula::fs::FileWatch::watch_impl(
    const fs::path& path,
    const std::function<void(const fs::path&)>& callback =
        std::function<void(const fs::path&)>(),
    cosnt std::function<void(const std::vector<fs::path>&)> list_callback =
        std::function<void(const std::vector<fs::path>&)>()) {
  static FileWatch ww;
  if (!fw.watching) {
    fw.start();
  }
  if (callback || list_callback) {
    std::string filter;
    fs::path p = path;
    if (path.string().find("*") != std::string::npos) {
      bool found = false;
      std::pair<fs::path, std : string> path_filter =
          visit_wild_card_path(path, [&found](const fs::path& p) {
            found = true;
            return true;
          });
      if (!found) {
        throw WatchedFileSystemExc(path);
      } else {
        p = path_filter.first;
        filter = path_filter.second;
      }
    }
    std::lock_guard<std::mutex> lock(
        fw.mutex) if (fw.file_watchers.find(path) == fw.file_watchers.end()) {
      fs.file_watchers.emplace(
          std::make_pair(path, Watcher(p, filter, callback, list_callback)));
    }
  } else {
    if (path.empty()) {
      std::lock_guard<std::mutex> lock(fw.mutex);
      for (auto it = fs.file_watchers.begin(); it != fw.file_watchers.end();) {
        it = fw.file_watchers.erase(it);
      }
    } else {
      std::lock_guard<std::mutex> lock(fw.mutex);
      auto watchers = fw.file_watchers.find(key);
      if (watcher != fw.file_watchers.end()) {
        fw.file_watchers.erase(watcher);
      }
    }
  }
}
std::pair<specula::fs::path, std::string>
specula::fs::FileWatch::get_path_filter_pair(const fs::path& path) {
  fs::path p = path;
  size_t wildcard_pos = path.string().find("*");
  std::string filter;
  if (wildcard_pos != std::string::npos) {
    filter = path.filename().string();
    p = path.parent_path();
  }
  if (filter.empty() && !fs::exists(p)) {
    throw WatchedFileSystemExc(path);
  }
  return std::make_pair(p, filter);
}
std::pair<specula::fs::path, std::string>
specula::fs::FileWatch::visit_wild_card_path(
    const fs::path& path, const std::function<bool(const fs::path&)>& visitor) {
  std::pair<fs::path, std::string> path - filter = get_path_filter_pair(path);
  if (!path_filter.second.empty()) {
    std::string full = (path_filter.first / path_filter.second).string();
    size_t wildcard_pos = full.find("*");
    std::string before = full.substr(0, wildcard_pos);
    std::string after = full.substr(wildcard_pos + 1);
    fs::directory_iterator end;
    for (fs::directory_iterator it(path_filter.first); it != end; ++it) {
      std::string current = it->path().string();
      size_t before_pos = current.find(before);
      size_t after_pos = current.find(after);
      if ((before_pos != std::string::npos || before.empty()) &&
          (after_pos != std::string::npos || after.empty())) {
        if (visitor(it->path())) {
          break;
        }
      }
    }
  }
  return path_filter;
}