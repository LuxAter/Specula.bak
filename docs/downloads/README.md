# Installation

The download will provide a package with all of the necessary requirements to
run the program, including the program itself. Simply unzip the file in your
prefered directory and begin using the software.

# Source Code

To build form source code, there are a few requirements before you can compile
the executable. First install ``git``, ``cmake``, and any modern C++ compiler
that supports C++17.

!> Compiling on Windows and OSX is currently failing, and without a machine
to develop on, other operating systems will not be supported.

Once those have been installed follow these commands to compile to executable.

```bash
mkdir build && cd build;
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```

This will produce an executable ``specula``, and copy the examples directory.
So to run the ``box`` example, simply execute

```bash
./specula examples/box.lua
```
