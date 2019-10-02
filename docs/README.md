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
