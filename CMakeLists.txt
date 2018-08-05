cmake_minimum_required(VERSION 3.7)
project(POJSolutions)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(chapter10-match)
add_subdirectory(chapter22-DP-interval)
add_subdirectory(chapter11-maximum-flow)
set(SOURCE_FILES post_office_1160.cpp)
add_executable(POJSolutions ${SOURCE_FILES})