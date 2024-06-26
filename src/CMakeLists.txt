set(TARGET_NAME cpplib)
set(PUBLIC_HEADERS_DIR ${CMAKE_SOURCE_DIR}/include/cpplib)

set(SOURCE_CODE
    utils/sqrt.cpp
    utils/sqrt.hpp
    vec2.cpp
)

set(PUBLIC_HEADERS
    "${PUBLIC_HEADERS_DIR}/vec2.hpp"
)

add_library(${TARGET_NAME} ${SOURCE_CODE})

target_include_directories(${TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/matlib>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)

if (BUILD_SHARED_LIBS)
    set_target_properties(${TARGET_NAME} PROPERTIES
        VERSION ${cpplib_VERSION_MAJOR}.${cpplib_VERSION_MINOR}.${cpplib_VERSION_PATCH}
        SOVERSION ${cpplib_VERSION_MAJOR}
    )
endif()

include(GenerateExportHeader)
generate_export_header(${TARGET_NAME})