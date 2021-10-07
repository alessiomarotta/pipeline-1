cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
project(pipeline-1)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(pipeline-1 ${SOURCES})
