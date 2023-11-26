# ============================================================================
# ------------------------------ Post build ----------------------------------

set (TARGET_PATH ${CMAKE_CURRENT_BINARY_DIR}/matrix)

if (CMAKE_BUILD_TYPE MATCHES Release)
    # Code signing
    add_custom_command(TARGET matrix
            POST_BUILD
            COMMAND ${CMAKE_SOURCE_DIR}/cmake/codesign.sh
            ARGS ${TARGET_PATH}
            )
endif ()
