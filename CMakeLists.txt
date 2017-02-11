cmake_minimum_required(VERSION 3.6)
project(MicroMouse)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include_directories(.)
#include_directories(src)
#include_directories(src/main)
include_directories(src/main/cc)
include_directories(src/main/cc/robot)
include_directories(src/main/cc/robot/impl)
include_directories(src/main/cc/maze)
include_directories(src/main/cc/maze/impl)
include_directories(src/main/cc/maze/cell)
include_directories(src/main/cc/util)
#include_directories(src/main/c)
#include_directories(src/main/c/com/micromouse/maze)
#include_directories(src/main/c/com/micromouse/hardware)
#include_directories(src/main/c/com/micromouse/location)
#include_directories(src/main/c/com/micromouse/robot)
include_directories(src/test/cc)

#FILE(GLOB_RECURSE SRCFILES src/main/c/*.c src/main/c/*.h)
FILE(GLOB_RECURSE SRCFILES src/main/cc/*.cc src/main/cc/*.h)

set(SOURCE_FILES ${SRCFILES} main.cc)

add_executable(MicroMouse ${SOURCE_FILES})