cmake_minimum_required(VERSION 3.2)

project(pmqtt)

# default close DEBUG mode
OPTION(DEBUG "add debug flags" OFF)

if (DEBUG)
    message(STATUS "Configuring build for debug")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wunused -Werror -std=c11 -D_POSIX_C_SOURCE=200112L -Og -pedantic -luuid -ggdb -fsanitize=address -static-libasan -fsanitize=undefined -fno-omit-frame-pointer -pg")
else (DEBUG)
    message(STATUS "Configuring build for production")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wunused -Werror -Wextra -std=c11 -D_POSIX_C_SOURCE=200112L -O3 -luuid -pedantic")
endif (DEBUG)

# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

file(GLOB SOURCES lib/*.c)

set(AUTHOR "pedrogao")
set(LICENSE "MIT")

# tests
add_subdirectory(tests)
# app
add_subdirectory(app)

add_library(pmqtt_shared SHARED ${SOURCES})

