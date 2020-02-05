#ifndef SPECULA_FWATCH_HPP_
#define SPECULA_FWATCH_HPP_

#include <atomic>
#include <map>
#include <mutex>
#include <regex>
#include <string>
#include <thread>
#include <vector>

#include <ghc/fs_std.hpp>

namespace specula {
namespace fs {
using namespace ::fs;
/**
 * @brief File/Path watcher
 *
 * This class implements a file/directory watcher. Every time a file matching
 * the regular expression provided, a callback is called with the updated file.
 * This is done through creating a thread that sleeps for a given delay, then
 * recursively checks all files in the base path. If a file satisfies the
 * regular expression, then it retrieves the updated file time.
 *
 * This is very inefficient as every check all files in the direction must be
 * recursively checked.
 *
 * @todo Implement an alternative that method that does not check for new files,
 * but will message when an existing file is modified or deleted.
 */
class Watcher {
public:
  /**
   * @brief File update event that occurred.
   */
  enum Event {
    MODIFIED, //!< Existing file was modified
    CREATED,  //!< New file was created
    DELETED   //!< Existing file was deleted
  };
  /**
   * @brief Creates a file watcher with a general callback
   *
   * Constructs a file watcher from the regular expression, and checks for
   * updates every `delay`, if any file is created, modified, or deleted, then
   * the callback function is called.
   *
   * @param watch_path File path regular expression
   * @param callback General callback function
   * @param delay Delay between checking for updates
   */
  Watcher(
      std::string watch_path,
      const std::function<void(const ::fs::path&, const Event&)>& callback,
      ::fs::file_time_type::duration delay = std::chrono::milliseconds(5000));
  /**
   * @brief Creates a file watcher with a modified callback
   *
   * Constructs a file watcher from the regular expression, and checks for
   * updates every `delay`, if any file is modified, then the callback function
   * is called.
   *
   * @param watch_path File path regular expression
   * @param modified_callback File modified callback function
   * @param delay Delay between checking for updates
   */
  Watcher(
      std::string watch_path,
      const std::function<void(const ::fs::path&)>& modified_callback,
      ::fs::file_time_type::duration delay = std::chrono::milliseconds(5000));
  /**
   * @brief Creates a file watcher with specific event callbacks
   *
   * Constructs a file watcher from the regular expression, and checks for
   * updates every `delay`, if any file is created, then the `created_callback`
   * function is called, if any file is modified, then the `modified_callback`
   * function is called, and if any file is deleted, then the
   * `deleted_callback` function is called.
   *
   * @param watch_path File path regular expression
   * @param created_callback File created callback function
   * @param modified_callback File modified callback function
   * @param deleted_callback File deleted callback function
   * @param delay Delay between checking for updates
   */
  Watcher(
      std::string watch_path,
      const std::function<void(const ::fs::path&)>& created_callback,
      const std::function<void(const ::fs::path&)>& modified_callback,
      const std::function<void(const ::fs::path&)>& deleted_callback,
      ::fs::file_time_type::duration delay = std::chrono::milliseconds(5000));
  /**
   * @brief Destroys and stops file watcher
   *
   * If file watcher is active, then it is first stooped before destruction is
   * finished.
   */
  ~Watcher();

  /**
   * @brief Update delay between update checks
   *
   * This updates the delay between file checks in a safe manner.
   *
   * @param new_delay New duration to sleep between file update checks.
   */
  void set_delay(::fs::file_time_type::duration new_delay);

  /**
   * @brief Starts the file watcher
   *
   * This function creates the new thread that will occasionally check for
   * updates to the tracked files.
   *
   * This function is called by the constructor.
   */
  void start();
  /**
   * @brief Stops the file watcher
   *
   * This function stops the thread that checks for file updates, and joins it
   * if applicable.
   *
   * This function is called by the destructor.
   */
  void stop();

private:
  void generate_filter(std::string watch_path);

  ::fs::path root_path;
  std::unique_ptr<std::regex> filter;

  ::fs::file_time_type::duration delay;
  std::function<void(const ::fs::path&, const Event&)> callback;
  std::function<void(const ::fs::path&)> created_callback;
  std::function<void(const ::fs::path&)> modified_callback;
  std::function<void(const ::fs::path&)> deleted_callback;

  std::mutex mutex;
  std::atomic<bool> watching;
  std::unique_ptr<std::thread> watcher_thread;

  std::map<::fs::path, ::fs::file_time_type> modified_times;
};
} // namespace fs
} // namespace specula

#endif // SPECULA_FWATCH_HPP_
