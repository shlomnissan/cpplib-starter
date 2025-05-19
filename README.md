# 🔨 Modern C++ Library Starter

![ubuntu-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/ubuntu.yml/badge.svg)
![windows-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/windows.yml/badge.svg)
![macos-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/macos.yml/badge.svg)
[![docs-badge](https://img.shields.io/badge/docs-online-blue.svg)](https://shlomnissan.github.io/cpplib-starter/)

This repository provides a modern, cross-platform starter template for building C++ libraries.
It incorporates best practices in project structure, build systems, package management, testing, and documentation.

If you're starting a new C++ library project, this template is designed to help you move quickly and confidently.

## Key Features

- **Clean project structure** following the [Pitchfork Layout](https://github.com/vector-of-bool/pitchfork?tab=readme-ov-file) (PFL).
- **Modern CMake** configuration:
  - Cross-platform builds (Windows, macOS, Linux).
  - Hidden symbols by default to enforce a clear public API.
  - Semantic versioning integrated into the build system.
  - Fully installable and importable as a CMake package.
  - Seamless unit test integration.
- **Package management** using [vcpkg](https://vcpkg.io/en/).
- **Continuous Integration** with GitHub Actions:
  - Automated builds and tests on Windows, macOS, and Linux.
- **Unit testing** setup with [GoogleTest](https://github.com/google/googletest).
- **Documentation generation** ready with [Doxygen](https://www.doxygen.nl/).

## CMake Configuration
While this starter project supports multiple distribution formats, shared libraries are preferred for their controlled symbol visibility, reduced binary size, dynamic versioning support, and lower runtime memory usage. The following subsections assume distribution via a shared library.

### Dependency Management and Presets
This project utilizes [vcpkg](https://vcpkg.io/en/) for dependency management and CMake presets to streamline configuration across different platforms and build types.
#### Managing Dependencies with vcpkg.json
In [manifest mode](https://learn.microsoft.com/en-us/vcpkg/consume/manifest-mode), dependencies are declared in a `vcpkg.json` file located at the root of your project. This approach ensures that all team members and CI environments use the same set of dependencies, promoting consistency and reproducibility.

To add a new dependency, such as `gtest`, you can manually edit the `vcpkg.json` file:
```json
{
  "dependencies": [
    {
      "name": "gtest",
      "version>=": "1.15.2"
    }
  ]
}
```
> vcpkg resolves and installs any required transitive dependencies automatically.

#### Configuring Builds with CMake Presets
CMake presets simplify the configuration and build process by encapsulating common settings. In this project, the `CMakePresets.json` file defines two primary presets:
```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "debug",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug",
        "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      }
    },
    {
      "name": "release",
      "binaryDir": "${sourceDir}/release",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release",
        "BUILD_SHARED_LIBS": "ON",
        "BUILD_TESTS": "OFF",
        "CMAKE_MSVC_RUNTIME_LIBRARY": "MultiThreadedDLL",
        "CMAKE_TOOLCHAIN_FILE": "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
      }
    }
  ]
}
```
To configure and build the project using these presets, run:
```bash
cmake --preset=debug
cmake --build --preset=debug
```
or
```bash
cmake --preset=release
cmake --build --preset=release
```
> Ensure the VCPKG_ROOT environment variable is set so that the presets can locate the vcpkg toolchain file correctly.

Presets help enforce consistency across CI, local development, and packaging. You can easily extend them with additional presets for custom builds, testing, or platform-specific options.
