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
   - Options
   - [Dependency Management and Presets](#dependency-management-and-presets)
   - [Symbol Visibility](#symbol-visibility)
   - [Semantic Versioning](#semantic-versioning)
   - Installation
- Unit Testing
- Documentation
- Scripts

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
