cmake_minimum_required(VERSION 3.20)

file(READ "version.txt" VERSION_FILE)

project(cpplib VERSION ${VERSION_FILE})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINE_HIDDEN ON)

option(BUILD_TESTS "build tests" ON)

add_subdirectory(src)

if (BUILD_TESTS)
    include(CTest)
endif()