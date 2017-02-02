cmake_minimum_required(VERSION 3.6)
project(MicroMouse)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

include_directories(.)
include_directories(src)
include_directories(src/main)
include_directories(src/main/c)
include_directories(src/main/c/com/micromouse/maze)
include_directories(src/main/c/com/micromouse/hardware)
include_directories(src/main/c/com/micromouse/location)
include_directories(src/main/c/com/micromouse/robot)
include_directories(src/test/c)

FILE(GLOB_RECURSE SRCFILES src/main/c/*.c src/main/c/*.h)

set(SOURCE_FILES ${SRCFILES} main.c src/main/c/com/micromouse/utility/vector/cell_vector.h src/main/c/com/micromouse/utility/vector/cell_vector.c)

add_executable(MicroMouse ${SOURCE_FILES})