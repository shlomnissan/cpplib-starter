# 🔨 Modern C++ Library Starter

![ubuntu-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/ubuntu-test.yml/badge.svg)
![windows-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/windows-test.yml/badge.svg)
![macos-test-badge](https://github.com/shlomnissan/cpplib-starter/actions/workflows/macos-test.yml/badge.svg)

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
