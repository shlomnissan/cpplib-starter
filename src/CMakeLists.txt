set(PUBLIC_HEADERS_DIR ${CMAKE_SOURCE_DIR}/include/cpplib)

set(SOURCE_CODE
    math.cpp
    math.hpp
    vector2.cpp
)

set(PUBLIC_HEADERS
    ${PUBLIC_HEADERS_DIR}/vector2.hpp
)

if(NOT_APPLE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()

add_library(cpplib ${SOURCE_CODE} ${PUBLIC_HEADERS})

target_include_directories(cpplib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)

set_target_properties(cpplib PROPERTIES
    VERSION ${cpplib_VERSION_MAJOR}.${cpplib_VERSION_MINOR}.${cpplib_VERSION_PATCH}
    SOVERSION ${cpplib_VERSION_MAJOR}
)

include(GenerateExportHeader)
generate_export_header(cpplib)