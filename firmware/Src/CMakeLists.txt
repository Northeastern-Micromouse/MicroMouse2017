cmake_minimum_required(VERSION 3.6)
project(MicroMouse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(../../firmware)
include_directories(../../firmware/inc)
include_directories(../../firmware/inc/AL)
include_directories(../../firmware/inc/PAL)
include_directories(../../firmware/inc/PHIL)
include_directories(../../firmware/src)
include_directories(../../firmware/src/AL)
include_directories(../../firmware/src/PAL)
include_directories(../../firmware/src/PHIL)

FILE(GLOB_RECURSE SRCFILES *.cpp *.c **/*.cpp ../inc/*.h ../inc/**/*.h)

set(SOURCE_FILES ${SRCFILES} main.c)

add_executable(Firmware ${SOURCE_FILES})

