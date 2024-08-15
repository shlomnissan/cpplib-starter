find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    add_custom_target(doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG_FILE}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else()
    message(WARNING "Unable to build documentation. Please ensure that Doxygen is installed on your system.")
endif()