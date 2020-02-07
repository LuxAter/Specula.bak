#ifndef SPECULA_VERSION_HPP_
#define SPECULA_VERSION_HPP_

#define SPECULA_VERSION_MAJOR 3
#define SPECULA_VERSION_MINOR 0
#define SPECULA_VERSION_PATCH 0

inline void get_version(unsigned &major, unsigned &minor, unsigned &patch) {
  major = SPECULA_VERSION_MAJOR;
  minor = SPECULA_VERSION_MINOR;
  patch = SPECULA_VERSION_PATCH;
}

#endif // SPECULA_VERSION_HPP_
