# 🔨 Modern C++ Library Starter

![ubuntu-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/ubuntu.yml/badge.svg)
![windows-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/windows.yml/badge.svg)
![macos-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/macos.yml/badge.svg)
[![docs-badge](https://img.shields.io/badge/docs-online-blue.svg)](https://shlomnissan.github.io/cpplib-starter/)

This repository provides a modern, cross-platform starter template for building C++ libraries.
It incorporates best practices in project structure, build systems, package management, testing, and documentation.

If you're starting a new C++ library project, this template is designed to help you move quickly and confidently.

## Contents
- [Key Features](#key-features)
- Getting Started
- Project Structure
- [CMake Configuration](#cmake-configuration)
   - [CMake Options](#cmake-options)
   - [Dependency Management and Presets](#dependency-management-and-presets)
   - [Symbol Visibility](#symbol-visibility)
   - [Semantic Versioning](#semantic-versioning)
   - [Installation](#installation)
- Unit Testing
- Documentation

## Key Features

- **Clean project structure** following the [Pitchfork Layout](https://github.com/vector-of-bool/pitchfork?tab=readme-ov-file) (PFL).
- **Modern CMake** configuration:
  - **Cross-platform** builds (Windows, macOS, Linux).
  - Hidden symbols by default to enforce a clear public API.
  - Semantic versioning integrated into the build system.
  - Fully installable and importable as a CMake package.
  - Seamless unit test integration.
- **Package management** using [vcpkg](https://vcpkg.io/en/).
- **Continuous Integration** with GitHub Actions:
  - Automated builds and tests on Windows, macOS, and Linux.
  - Automated documentation generation and deployment to [GitHub Pages](https://pages.github.com/).
- **Unit testing** setup with [GoogleTest](https://github.com/google/googletest).
- **Documentation generation** ready with [Doxygen](https://www.doxygen.nl/).

## CMake Configuration
While this starter project supports multiple distribution formats, shared libraries are preferred for their controlled symbol visibility, dynamic versioning support, reduced binary size, and lower runtime memory usage. The following subsections assume distribution via a shared library.

### CMake Options

This project defines several configurable CMake options to tailor the build process. While you can set these manually via `-D` flags, it’s recommended to use the provided CMake presets to ensure consistency across environments.

| Option              | Type           | Default | Description                                                                 |
|---------------------|----------------|---------|-----------------------------------------------------------------------------|
| `BUILD_TESTS`       | Custom         | `ON`    | Enables unit test targets. When disabled, test code and dependencies are excluded. |
| `BUILD_DOCS`        | Custom         | `ON`    | Enables building documentation. When disabled, doc generation target is skipped. |
| `BUILD_SHARED_LIBS` | Standard       | `OFF`   | Determines whether the library is built as a shared or static library.|


The default values above apply when configuring the project manually. However, the provided CMake presets are the recommended way to configure builds:
- The `debug` preset enables both tests and documentation.
- The `release` preset disables tests and documentation but enables `BUILD_SHARED_LIBS`.

To configure the project manually without presets, you can set options like this:
```bash
cmake -DBUILD_TESTS=OFF -DBUILD_DOCS=OFF -DBUILD_SHARED_LIBS=ON -B build
```
Still, using presets is the preferred method to enforce consistent builds across local development and CI.

### Dependency Management and Presets
This project uses [vcpkg](https://vcpkg.io/en/) for dependency management (see the _Getting Started_ section for installation instructions) and relies on CMake presets to simplify configuration across platforms and build types.

#### Managing Dependencies with vcpkg.json
In [manifest mode](https://learn.microsoft.com/en-us/vcpkg/consume/manifest-mode), dependencies are declared in a vcpkg.json file located at the root of your project. This approach ensures that all team members and CI environments use the same set of dependencies, promoting consistency and reproducibility.

To add a new dependency, simply edit the `vcpkg.json` file directly. At the moment, it includes only gtest as a dependency.

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
#### Configuring Builds with CMake Presets
CMake presets streamline the configuration and build process by capturing common settings. This project’s `CMakePresets.json` defines two main presets: `debug` and `release`. To configure and build the project with one of these presets, run:
```bash
cmake --preset=debug
cmake --build --preset=debug
```
or
```bash
cmake --preset=release
cmake --build --preset=release
```
Presets help enforce consistency across CI, local development, and packaging. You can easily extend them with additional presets for custom builds, testing, or platform-specific options.

### Symbol Visibility

Symbol visibility determines which functions, classes, or variables in a compiled library are accessible to other programs. On Windows, symbols are hidden by default and must be explicitly marked for export when building a DLL. On Unix-like systems, symbols are visible by default unless compiler flags (like `-fvisibility=hidden`) are used to hide them.

Controlling symbol visibility is important for building clean and efficient shared libraries. It helps prevent naming conflicts, improves load times, and hides internal implementation details. This results in a safer, more maintainable library with better runtime performance.

To ensure consistent symbol visibility across platforms, this project uses CMake’s `GenerateExportHeader` module. It generates a header file (e.g., `cpplib_export.h`) that defines an export macro (e.g., `CPPLIB_EXPORT`) used to mark public symbols. By default, all symbols are hidden unless explicitly annotated with this macro.

> The header file and macro name are automatically derived from the project name defined in the root `CMakeLists.txt`. For example, `project(cpplib)` produces `cpplib_export.h` with the macro `CPPLIB_EXPORT`. Renaming the project will regenerate these accordingly, unless you override them manually.

To expose a symbol as part of the library’s public API, mark it with the generated export macro. For example:

```cpp
// public_api.h
#include "cpplib_export.h"

// Exported class
class CPPLIB_EXPORT MyClass {
public:
    void doWork();
};

// Exported function
CPPLIB_EXPORT void doSomething();

// Exported global variable
CPPLIB_EXPORT extern int myGlobalCounter;
```
Make sure all classes, functions, and global variables in your public headers are properly annotated. Any symbol included in a public header must be exported to be accessible outside the library, while symbols used only in implementation files can remain hidden and unannotated.

### Semantic Versioning

Semantic versioning ([semver](https://semver.org/) is a versioning scheme that communicates the nature of changes in a library through a three-part version number: `MAJOR.MINOR.PATCH`. This convention helps consumers of your library understand what to expect with each release and whether they can safely upgrade without breaking their code.

- **MAJOR** version changes indicate breaking API changes.
- **MINOR** version changes add functionality in a backward-compatible manner.
- **PATCH** version changes are backward-compatible bug fixes.

Following semver is especially important for shared libraries, where ABI stability matters. A consumer building against version 1.2.0 should be able to upgrade to 1.2.5 without recompiling, but upgrading to 2.0.0 may require code changes or rebuilding due to possible breaking changes.

On platforms like Linux, versioning also affects how the dynamic linker resolves shared library dependencies. For example, versioned `.so` files (`libcpplib.so.1`) allow different versions to coexist or be symbolically linked for ABI compatibility.

This project sets the version in the root CMakeLists.txt using:

```cpp
project(cpplib VERSION 0.0.1)
```

CMake automatically defines version variables like `yourlib_VERSION`, `yourlib_VERSION_MAJOR`, and so on, based on the `project()` declaration. You can use these in your headers or embed them in metadata as needed. This project also sets the `VERSION` and `SOVERSION` properties on the library target (in `src/CMakeLists.txt`) to control how versioned `.so` or `.dylib` files are named:

```cpp
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${cpplib_VERSION_MAJOR}.${cpplib_VERSION_MINOR}.${cpplib_VERSION_PATCH}
    SOVERSION ${cpplib_VERSION_MAJOR}
)
```
> Just like with the export macro, these variable names are tied to the project name. When you rename the project, you'll need to update the variable names accordingly (see the _Getting Started_ section).

### Installation

This project includes platform-specific installation scripts to streamline the entire build and install process. These scripts configure the project using the appropriate CMake preset, build it in `release/`, and install the resulting library and headers to your system.

From the root of the project, run:
- On Unix/macOS:
```bash
./scripts/install.sh
```
- On Windows (in `cmd.exe`):
```c
scripts\install.bat
```

These scripts:
- Clean any previous `release/` builds.
- Configure the project using the `release` preset.
- Build the release version of the library.
- Install it system-wide.

> On Unix-like systems, installation may require `sudo`. To change the install prefix, modify the script or preset to set `CMAKE_INSTALL_PREFIX`.

To install manually, you can replicate the script steps:

```bash
cmake --preset=release
cmake --build --preset=release
sudo cmake --install release
```

#### Consuming the Installed Library

Once installed, the library can be used in any CMake-based project via `find_package()`:

```cmake
find_package(mylib REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE cpplib::cpplib)
```

This template installs a namespaced target in the form `cpplib::cpplib`, where `cpplib` is the project name defined in your root `CMakeLists.txt` (e.g., `project(cpplib VERSION 0.0.1)`). When you rename the project, the exported target, version files, and export macro will all reflect the new name (e.g., `mylib::mylib`).

The imported target includes:
- Correct include paths and compile definitions.
- Linker settings for static or shared builds.
- Version metadata for compatibility validation.

> This CMake package is fully relocatable and supports consumption from both system-wide installs and local `CMAKE_PREFIX_PATH` overrides.

If you prefer not to use CMake in your consumer project, you can link the installed library manually using your system compiler. For example, if the library was installed to `/usr/local` and named `libmylib`.so or `libmylib.a`, you can compile like this:

```bash
clang++ -std=c++23 main.cpp -I/usr/local/include -L/usr/local/lib -lmylib
```

Make sure to adjust the include and library paths based on your installation prefix.

## Unit Testing
