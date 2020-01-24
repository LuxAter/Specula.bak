#ifndef SPECULA_VERSION_HPP_
#define SPECULA_VERSION_HPP_

#define SPECULA_VERSION_MAJOR 2
#define SPECULA_VERSION_MINOR 2
#define SPECULA_VERSION_PATCH 8

inline void get_version(unsigned &major, unsigned &minor, unsigned &patch) {
  major = SPECULA_VERSION_MAJOR;
  minor = SPECULA_VERSION_MINOR;
  patch = SPECULA_VERSION_PATCH;
}

#endif // SPECULA_VERSION_HPP_
