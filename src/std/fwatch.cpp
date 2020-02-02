#include "specula/std/fwatch.hpp"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "specula/dev.hpp"
#include "specula/std/filesystem.hpp"

specula::fs::WatchedFileSystemExc::WatchedFileSystemExc(const fs::path& path) {
  snprintf(message, 4096, "Failed to find file or directory at: %s",
           path.c_str());
  LERROR(message);
}
const char* specula::fs::WatchedFileSystemExc::what() const throw() {
  return message;
}

specula::fs::FileWatch::~FileWatch() {
  unwatch_all();
  watching = false;
  if (thread->joinable())
    thread->join();
}
void specula::fs::FileWatch::watch(
    const fs::path& path,
    const std::function<void(const fs::path&)>& callback) {
  watch_impl(path, callback,
             std::function<void(const std::vector<fs::path>&)>());
}
void specula::fs::FileWatch::watch(
    const fs::path& path,
    const std::function<void(const std::vector<fs::path>&)>& callback) {
  watch_impl(path, std::function<void(const fs::path&)>(), callback);
}
void specula::fs::FileWatch::unwatch(const fs::path& path) { watch_impl(path); }
void specula::fs::FileWatch::unwatch_all() { watch_impl(fs::path()); }
void specula::fs::FileWatch::touch(const fs::path& path,
                                   fs::file_time_type time) {
  if (fs::exists(path)) {
    fs::last_write_time(path, time);
  } else if (path.string().find("*") != std::string::npos) {
    visit_wild_card_path(path, [time](const fs::path& p) {
      fs::last_write_time(p, time);
      return false;
    });
  } else {
    throw WatchedFileSystemExc(path);
  }
}

specula::fs::FileWatch::Watcher::Watcher() {}
specula::fs::FileWatch::Watcher::Watcher(
    const fs::path& path, const std::string& filter,
    const std::function<void(const fs::path&)>& callback,
    const std::function<void(const std::vector<fs::path>&)>& list_callback)
    : path(path), filter(filter), callback(callback),
      list_callback(list_callback) {
  if (!filter.empty()) {
    std::vector<fs::path> paths;
    visit_wild_card_path(path / filter, [this, &paths](const fs::path& p) {
      has_changed(p);
      paths.push_back(p);
      return false;
    });
    if (callback) {
      callback(path / filter);
    } else {
      list_callback(paths);
    }
  }
}
void specula::fs::FileWatch::Watcher::watch() {
  if (filter.empty() && has_changed(path) && callback) {
    callback(path);
  } else if (!filter.empty()) {
    std::vector<fs::path> paths;
    visit_wild_card_path(path / filter, [this, &paths](const fs::path& p) {
      bool path_has_changed = has_changed(p);
      if (path_has_changed && callback) {
        callback(path / filter);
        return true;
      } else if (path_has_changed && list_callback) {
        paths.push_back(p);
      }
      return false;
    });
    if (paths.size() && list_callback) {
      list_callback(paths);
    }
  }
}
bool specula::fs::FileWatch::Watcher::has_changed(const fs::path& path) {
  fs::file_time_type time = fs::last_write_time(path);
  if (modification_times.find(path_hash(path)) == modification_times.end()) {
    modification_times[path_hash(path)] = time;
    return true;
  }
  fs::file_time_type& prev = modification_times[path_hash(path)];
  if (prev < time) {
    prev = time;
    return true;
  }
  return false;
}

specula::fs::FileWatch::FileWatch() : watching(false) {}
void specula::fs::FileWatch::close() {
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
        std::lock_guard<std::mutex> lock(mutex);
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
    const fs::path& path, const std::function<void(const fs::path&)>& callback,
    const std::function<void(const std::vector<fs::path>&)> list_callback) {
  static FileWatch fw;
  if (!fw.watching) {
    fw.start();
  }
  if (callback || list_callback) {
    std::string filter;
    fs::path p = path;
    if (path.string().find("*") != std::string::npos) {
      bool found = false;
      std::pair<fs::path, std::string> path_filter =
          visit_wild_card_path(path, [&found](const fs::path&) {
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
    std::lock_guard<std::mutex> lock(fw.mutex);
    if (fw.file_watchers.find(path_hash(path)) == fw.file_watchers.end()) {
      fw.file_watchers.emplace(std::make_pair(
          path_hash(path), Watcher(p, filter, callback, list_callback)));
    }
  } else {
    if (path.empty()) {
      std::lock_guard<std::mutex> lock(fw.mutex);
      for (auto it = fw.file_watchers.begin(); it != fw.file_watchers.end();) {
        it = fw.file_watchers.erase(it);
      }
    } else {
      std::lock_guard<std::mutex> lock(fw.mutex);
      auto watcher = fw.file_watchers.find(path_hash(path));
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
  std::pair<fs::path, std::string> path_filter = get_path_filter_pair(path);
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
std::hash<specula::fs::path> specula::fs::FileWatch::path_hash =
    std::hash<specula::fs::path>();
