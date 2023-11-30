add_executable(matrix matrix.c)

add_compile_options(-Wall -Werror -pedantic)

install(TARGETS matrix DESTINATION ${CMAKE_SOURCE_DIR}/dist)

if (APPLE)
    include (${CMAKE_SOURCE_DIR}/cmake/macos.cmake)
endif ()
