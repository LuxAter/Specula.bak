#include "specula/std/filesystem.hpp"

#include <atomic>
#include <filesystem>
#include <map>
#include <mutex>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include "specula/dev/error.hpp"
#include "specula/dev/log.hpp"
#include "specula/dev/prof.hpp"

std::filesystem::Watcher::Watcher(
    std::string watch_path,
    const std::function<void(const std::filesystem::path&, const Event&)>&
        callback,
    std::filesystem::file_time_type::duration delay)
    : delay(delay), callback(callback), watching(false), modified_times({}) {
  generate_filter(watch_path);
  start();
}
std::filesystem::Watcher::Watcher(
    std::string watch_path,
    const std::function<void(const std::filesystem::path&)>& modified_callback,
    std::filesystem::file_time_type::duration delay)
    : delay(delay), modified_callback(modified_callback), watching(false),
      modified_times({}) {
  generate_filter(watch_path);
  start();
}
std::filesystem::Watcher::Watcher(
    std::string watch_path,
    const std::function<void(const std::filesystem::path&)>& created_callback,
    const std::function<void(const std::filesystem::path&)>& modified_callback,
    const std::function<void(const std::filesystem::path&)>& deleted_callback,
    std::filesystem::file_time_type::duration delay)
    : delay(delay), created_callback(created_callback),
      modified_callback(modified_callback), deleted_callback(deleted_callback),
      watching(false), modified_times({}) {
  generate_filter(watch_path);
  start();
}
std::filesystem::Watcher::~Watcher() { stop(); }

void std::filesystem::Watcher::set_delay(
    std::filesystem::file_time_type::duration new_delay) {
  std::lock_guard<std::mutex> lock(mutex);
  delay = new_delay;
}

void std::filesystem::Watcher::start() {
  if (!watching) {
    watching = true;
    for (auto& file :
         std::filesystem::recursive_directory_iterator(root_path)) {
      if (std::regex_match(file.path().string(), *filter)) {
        modified_times[file.path()] =
            std::filesystem::last_write_time(file.path());
      }
    }
    watcher_thread = std::unique_ptr<std::thread>(new std::thread([this]() {
      while (watching) {
        {
          std::lock_guard<std::mutex> lock(mutex);
          std::map<std::filesystem::path,
                   std::filesystem::file_time_type>::iterator it =
              modified_times.begin();
          while (it != modified_times.end()) {
            if (!std::filesystem::exists(it->first)) {
              if (callback)
                callback(it->first, DELETED);
              if (deleted_callback)
                deleted_callback(it->first);
              it = modified_times.erase(it);
            } else {
              ++it;
            }
          }

          for (auto& file :
               std::filesystem::recursive_directory_iterator(root_path)) {
            if (std::regex_match(file.path().string(), *filter)) {
              std::filesystem::file_time_type modified =
                  std::filesystem::last_write_time(file.path());
              if (modified_times.find(file.path()) == modified_times.end()) {
                modified_times[file.path()] = modified;
                if (callback)
                  callback(file.path(), CREATED);
                if (created_callback)
                  created_callback(file.path());
              } else if (modified_times[file.path()] < modified) {
                modified_times[file.path()] = modified;
                if (callback)
                  callback(file.path(), MODIFIED);
                if (modified_callback)
                  modified_callback(file.path());
              }
            }
          }
        }
        std::this_thread::sleep_for(delay);
      }
    }));
  }
}
void std::filesystem::Watcher::stop() {
  watching = false;
  if (watcher_thread->joinable())
    watcher_thread->join();
}

void std::filesystem::Watcher::generate_filter(std::string watch_path) {
  if (watch_path[0] != '/' && watch_path.compare(0, 2, "./") &&
      watch_path.compare(0, 3, "../") != 0) {

    watch_path = std::filesystem::current_path().string() + '/' + watch_path;
  }
  std::size_t wildcard_pos = watch_path.find_first_not_of(
      "/._- abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567789");
  if (wildcard_pos != std::string::npos) {
    root_path = std::filesystem::path(watch_path.substr(0, wildcard_pos))
                    .remove_filename();
    wildcard_pos = root_path.string().size();
    std::string filter_str = watch_path.substr(wildcard_pos);
    std::size_t pos = filter_str.find("**/");
    if (pos != std::string::npos) {
      filter_str.replace(pos, 3, "(([0-9]|[A-z]|[\\./_-])*/)?");
      pos = filter_str.find("*", 26);
    } else {
      pos = filter_str.find("*", 1);
    }
    if (pos != std::string::npos &&
        (filter_str[pos - 1] == '?' || filter_str[pos - 1] == '/')) {
      filter_str.replace(pos, 1, "[^/]+");
    }
    filter = std::unique_ptr<std::regex>(
        new std::regex((root_path / filter_str).string()));
  } else {
    root_path = std::filesystem::path(watch_path);
    filter = std::unique_ptr<std::regex>(
        new std::regex((root_path / ".*").string()));
  }
}
