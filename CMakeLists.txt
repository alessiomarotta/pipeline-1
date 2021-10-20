cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)
project(pipeline-1)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
list(REMOVE_ITEM SOURCES "src/Pipeline.cpp")
add_executable(pipeline-1 ${SOURCES})
