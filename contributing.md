# Contributing

To start contributing, first start by getting the code. Make all changes in a
feature branch ``feature/<name>``, this keeps the code more organized.

## Getting the Source 


The repository is stored on my personal Gitlab server. To clone it run

```bash
git clone git.ardenrasmussen.com/specula.git
```

## Dependencies

The only dependencies are ``git``, ``CMake``, and a modern C++ compiler (One
that supports C++17).

All other external dependencies of the project will be cloned by CMake if they
have not already been cloned into the project directory. All dependencies are
compiled by the build, so the first build can take some time.

## Compiling

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

## Testing

The tests should be executed, by running

```bash
make coverage
```

This will execute the tests, and capture coverage reports for the project. For
this project, I aim to have the code coverage always be over $75\%$.
