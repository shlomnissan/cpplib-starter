set(BUILD_GMOCK OFF CACHE BOOL "")
set(INSTALL_GTEST OFF CACHE BOOL "")

find_package(GTest REQUIRED)

if (NOT GTest_FOUND)
    message(STATUS "⚠️ GTest was not found. Use conan to install missing depedencies.")
    message(STATUS "  -- conan install . --output-folder=build --build=missing -sbuild_type=Debug")
    return()
endif()

file(GLOB TEST_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

foreach(TEST IN LISTS TEST_SOURCES)
    get_filename_component(FILE_NAME ${TEST} NAME)
    string(REGEX REPLACE "\\.[^.]*$" "" NAME_NO_EXT ${FILE_NAME})
    message(STATUS "🧪 Adding test ${FILE_NAME}")

    set(TEST_TARGET run_${NAME_NO_EXT})
    add_executable(${TEST_TARGET} ${TEST})
    target_link_libraries(${TEST_TARGET} PRIVATE gtest::gtest cpplib)
    add_test(${NAME_NO_EXT} ${TEST_TARGET})
endforeach()