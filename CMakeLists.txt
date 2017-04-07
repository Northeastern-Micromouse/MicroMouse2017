cmake_minimum_required(VERSION 3.6)
project(MicroMouse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(firmware)
include_directories(firmware/inc)
include_directories(firmware/inc/AL)
include_directories(firmware/inc/PHIL)
include_directories(firmware/inc/PAL)
add_subdirectory(firmware/src)
target_link_libraries(Firmware)

FILE(GLOB_RECURSE SRCFILES src/main/cc/**/*.cc src/main/cc/**/*.h)

set(SOURCE_FILES ${SRCFILES} main.cc)

add_executable(MicroMouse ${SOURCE_FILES})