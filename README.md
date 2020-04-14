<p align="center">

  <h1 align="center">SPECULA</h1>
  <p align="center">
    <a href="https://github.com/LuxAter/Specula/graphs/contributors"><img src="https://img.shields.io/github/contributors/LuxAter/Specula.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Specula/network/members"><img src="https://img.shields.io/github/forks/LuxAter/Specula.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Specula/stargazers"><img src="https://img.shields.io/github/stars/LuxAter/Specula.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Specula/issues"><img src="https://img.shields.io/github/issues/LuxAter/Specula.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Specula/blob/master/LICENSE.txt"><img src="https://img.shields.io/github/license/LuxAter/Specula.svg?style=flat-square"></a>
    <a href="https://github.com/LuxAter/Specula/releases"><img src="https://img.shields.io/github/tag/LuxAter/Specula.svg?include_prereleases&sort=semver&style=flat-square"></a>
    <a href="https://github.com/LuxAter/Specula/actions?query=workflows%3ADevelopment"><img src="https://img.shields.io/github/workflow/status/LuxAter/Specula/Development.svg?include_prereleases&sort=semver&style=flat-square"></a>
    <br/>
    A C++17 Physically Based Renderer
    <br/>
    <a href="https://luxater.github.io/Specula"><strong>Documentation</strong></a>
    <br/>
    <br/>
    <a href="https://github.com/LuxAter/Specula/releases">Downloads</a>
    ·
    <a href="https://github.com/LuxAter/Specula/issues/new?template=bug_report.md">Report Bug</a>
    ·
    <a href="https://github.com/LuxAter/Specula/issues/new?template=feature_request.md">Request Feature</a>
  </p>
</p>

## About the Project

There are many physically based renderers, and many which will produce results
of better quality and faster than Specula will. However, Specula is intended to
be used anywhere, and for educational purposes.

Specula is designed to have an easy to use API interface, so that the library
can be included in other programs. For example, Specula could be linked into a
physics simulation, and using the API it would allow direct output of photo
realistic renders from the simulation.

Specula is also written with a large focus on the readability of the code, and
the documentation that is generated in addition to the code. One should be able
to read through the documentation of the library, and leave with a functional
knowledge of physically based rendering for offline renderers.

### Built With

Specula depends on a number of frameworks which are included in the library.
Specifically

* [Catch2](https://github.com/catchorg/Catch2)
* [filesystem](https://github.com/gulrak/filesystem)
* [fmt](https://github.com/fmtlib/fmt)
* [OpenEXR](https://github.com/AcademySoftwareFoundation/openexr)
* [spdlog](https://github.com/gabime/spdlog)
* [stb](https://github.com/nothings/stb)

## Getting Started

These instructions will get you a copy of the renderer up and running on your
local machine for development and testing purposes.

### Prerequisites

The only prerequisites are [CMake](https://cmake.org/), and a C++ compiler
capable of C++17 (recommended to use [Clang](https://clang.llvm.org/)). Please
follow your system instructions for installing these.

### Installation

#### Prebuilt (recommended)

To get the library and the executable, goto the
[releases](https://github.com/LuxAter/Specula/releases) and download the file
from the latest release for your system. Currently Specula is compiled for
*Linux*, *Windows*, and *MacOs*. Simply extract the zip and execute the
``install`` script. This will copy the binaries and libraries the the
appropriate directories on your system.

#### Build from source

First get the source either from the
[releases](https://github.com/LuxAter/Specula/releases) page, or the preferred
method is to clone the repository.

```fish
git clone https://github.com/LuxAter/Specula.git
```

Now create a build directory, and configure the code using CMake.

```fish
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
```

Finally compile and install the code using GNUMake (or an alternative build
tool).

```fish
make install
```

## Usage

The specula render is shipped with a number of examples. Using the CLI
interface, one can render these examples with the following command.

```fish
specula-cli --xres=1920 --yres=1080 examples/cornell-box -output=cornell-box.png
```

Additional documentation for the command line usage can be found by executing.

```fish
specula-cli --help
```

*For more examples, please refer to the [Documentation](https://luxater.github.io/Specula/)*

## Contributing

Contributions are what make the open source community such an amazing place to
be, learn, inspire, and create. Any contributions you make are **greatly
appreciated**.

1. Fork the project
2. Create your feature branch (`git checkout -b feature/<my-feature>`)
3. Commit your changes (`git commit -m '<my-commit-message>'`)
4. Push to the branch (`git push origin feature/<my-feature>`)
5. Open a pull request

## License

Distributed under the GNU GPLv3 license. See
[`LICENSE.md`](https://github.com/LuxAter/Specula/blob/development/LICENSE.md)
for more information.
