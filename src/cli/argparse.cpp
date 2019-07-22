#include "cli/argparse.hpp"

#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "cli/color.hpp"
#include "util.hpp"

void specula::cli::ArgumentParser::add_option(const std::string &name,
                                              std::string help, Value val,
                                              bool positional) {
  std::string long_name = name;
  if (name.size() > 2 && name[1] == ',') {
    long_name = name.substr(2);
    name_map_[name[0]] = long_name;
  }
  options_[long_name] = val;
  if (positional) {
    positional_.push_back(long_name);
  }
  help_[name] = help;
}

void specula::cli::ArgumentParser::add_option(const std::string &name,
                                              std::string help,
                                              Value::ValueType type,
                                              bool positional) {
  std::string long_name = name;
  if (name.size() > 2 && name[1] == ',') {
    long_name = name.substr(2);
    name_map_[name[0]] = long_name;
  }
  options_[long_name] = Value(type);
  if (positional) {
    positional_.push_back(long_name);
  }
  help_[name] = help;
}

std::map<std::string, specula::cli::Value>
specula::cli::ArgumentParser::parse(int argc, char *argv[]) {
  // PARSE OPTIONS
  std::vector<std::string> remaining;
  exe_ = argv[0];
  for (std::size_t i = 1; i < static_cast<std::size_t>(argc); ++i) {
    if (strlen(argv[i]) <= 1) {
      continue;
    } else if (argv[i][0] == '-' && argv[i][1] == '-') {
      std::string name(argv[i]), value;
      if (name.find('=') != std::string::npos) {
        value = name.substr(name.find('=') + 1);
        name = name.substr(2, name.find('=') - 2);
      } else {
        name = name.substr(2);
      }
      std::map<std::string, Value>::iterator it;
      if ((it = options_.find(name)) != options_.end()) {
        it->second.count++;
        if (it->second.type_ == Value::ValueType::BOOL) {
          it->second.value = (it->second.value == "0") ? "1" : "0";
        } else {
          // if (it->second.implicit_value != std::string()) {
          it->second.value = it->second.implicit_value;
          // }
          if (value != std::string()) {
            it->second.value = value;
          } else if (i + 1 < static_cast<std::size_t>(argc) &&
                     argv[i + 1][0] != '-') {
            it->second.value = std::string(argv[i + 1]);
            i += 1;
          } else if (it->second.value == std::string()) {
            std::cout << bold(red(
                             fmt::fmt("expected an argument for '{}'", name)))
                      << std::endl;
          }
        }
      } else {
        std::cout << bold(yellow(fmt::fmt("unexpected option '{0}'", name)))
                  << std::endl;
      }
      // LONG NAME
    } else if (argv[i][0] == '-') {
      for (std::size_t j = 1; j < strlen(argv[i]); ++j) {
        std::map<char, std::string>::const_iterator it;
        if ((it = name_map_.find(argv[i][j])) != name_map_.end()) {
          options_[it->second].count++;
          if (options_[it->second].type_ == Value::ValueType::BOOL) {
            options_[it->second].value =
                (options_[it->second].value == "0") ? "1" : "0";
          } else {
            // if (options_[it->second].implicit_value != std::string()) {
            options_[it->second].value = options_[it->second].implicit_value;
            // }
            if (i + 1 < static_cast<std::size_t>(argc) &&
                j == strlen(argv[i]) - 1 && argv[i + 1][0] != '-') {
              options_[it->second].value = std::string(argv[i + 1]);
              i += 1;
              break;
            } else if (options_[it->second].value == std::string()) {
              std::cout << bold(red(fmt::fmt("expected an argument for '{}'",
                                             it->second)))
                        << std::endl;
            }
          }
        } else {
          std::cout << bold(yellow(
                           fmt::fmt("unexpected option '{}'", argv[i][j])))
                    << std::endl;
        }
      }
    } else {
      remaining.push_back(std::string(argv[i]));
    }
  }

  for (auto &it : remaining) {
    bool matched = false;
    for (auto &pos : positional_) {
      if (options_[pos].value == std::string()) {
        options_[pos].count++;
        options_[pos].value = it;
        matched = true;
        break;
      }
    }
    if (!matched) {
      std::cout << bold(yellow(fmt::fmt("unexpected option '{}'", it)))
                << std::endl;
    }
  }
  return options_;
}

void specula::cli::ArgumentParser::display_usage() {
  std::cout << exe_ << ' ';
  std::string usage;
  for (auto &it : options_) {
    if (it.second.type_ == Value::BOOL) {
      usage += fmt::fmt("[--{}]", it.first) + ' ';
    } else if (it.second.type_ == Value::NUMBER) {
      if (it.second.value == std::string() &&
          it.second.implicit_value == std::string()) {
        usage += fmt::fmt("--{} NUM", it.first) + ' ';
      } else if (it.second.value == std::string()) {
        usage += fmt::fmt("--{} [NUM]", it.first) + ' ';
      } else if (it.second.implicit_value == std::string()) {
        usage += fmt::fmt("[--{} NUM]", it.first) + ' ';
      } else {
        usage += fmt::fmt("[--{} [NUM]]", it.first) + ' ';
      }
    } else if (it.second.type_ == Value::STRING) {
      if (it.second.value == std::string() &&
          it.second.implicit_value == std::string()) {
        usage += fmt::fmt("--{} STR", it.first) + ' ';
      } else if (it.second.value == std::string()) {
        usage += fmt::fmt("--{} [STR]", it.first) + ' ';
      } else if (it.second.implicit_value == std::string()) {
        usage += fmt::fmt("[--{} STR]", it.first) + ' ';
      } else {
        usage += fmt::fmt("[--{} [STR]]", it.first) + ' ';
      }
    }
  }
  std::cout << fmt::wrap(usage, exe_.size() + 1) << std::endl;
}
void specula::cli::ArgumentParser::display_help() {
  std::size_t longest = 0;
  for (auto &it : help_) {
    longest = std::max(it.first.size(), longest);
  }
  for (auto &it : help_) {
    if (std::find(positional_.begin(), positional_.end(), it.first) ==
        positional_.end()) {
      if (it.first.size() > 2 && it.first[1] == ',') {
        std::cout << fmt::fmt(
                         " {:20}  {}",
                         fmt::fmt("-{} --{}", it.first[0], it.first.substr(2)),
                         fmt::wrap(it.second, 25))
                  << std::endl;
      } else {
        std::cout << fmt::fmt(" {:20}  {}", fmt::fmt("--{}", it.first),
                              fmt::wrap(it.second, 25))
                  << std::endl;
      }
    }
  }
  if (positional_.size() != 0) {
    std::cout << "POSITIONAL\n";
  }
  for (auto &it : help_) {
    if (std::find(positional_.begin(), positional_.end(), it.first) !=
        positional_.end()) {
      std::cout << fmt::fmt(" {:20}  {}", fmt::fmt("{}", it.first),
                            fmt::wrap(it.second, 25))
                << std::endl;
    }
  }
}
