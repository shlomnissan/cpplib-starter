cmake_minimum_required(VERSION 3.20)

project(cpplib_example)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(cpplib REQUIRED)

add_executable(cpplib_example main.cpp)

target_link_libraries(cpplib_example PRIVATE cpplib::cpplib)