# Specula

[![Travis (.org)](https://img.shields.io/travis/luxater/specula?style=for-the-badge)](https://travis-ci.org/LuxAter/Specula)
[![Codecov](https://img.shields.io/codecov/c/github/luxater/specula?style=for-the-badge)](https://codecov.io/gh/LuxAter/Specula)
[![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/luxater/specula?style=for-the-badge)](https://github.com/LuxAter/Specula)
[![Website](https://img.shields.io/website/https/luxater.github.io/Specula?down_color=red&down_message=offline&label=Documentation&style=for-the-badge&up_color=dark-green&up_message=online)](https://luxater.github.io/Specula)

Specula is a project to create a physical based rendering engine, which
utilizes Lua for the control and definition of the scenes.

## Installing

### Compiling From Source

#### Dependencies

The only dependencies are `git`, `CMake`, and a modern C++ compiler (One
that supports C++17).

All other external dependencies of the project will be cloned by CMake if they
have not already been cloned into the project directory. All dependencies are
compiled by the build, so the first build can take some time.

#### Compiling

I use CMake for compiling the code, as it is typically the standard for C++
projects. I encourage the use of out of source builds. So to build the
repository. Simply run the following commands.

```bash
mkdir cmake-build-debug && cd cmake-build-debug
cmake ..
make
```

This command will clone the most recent versions of the dependencies, and build
the core library, and the main test executable.

#### Installation

To install the binary and library, simplly run

```bash
mkdir cmake-build-release && cd cmake-build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
sudo make install
```

This will install the Specula library, the neccessary header files, and the
main executable.
