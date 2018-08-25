cmake_minimum_required(VERSION 3.7)
project(POJSolutions)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(chapter10-match)
add_subdirectory(chapter22-DP-interval)
add_subdirectory(chapter11-maximum-flow)
add_subdirectory(chapter7-segment-tree)
add_subdirectory(chapter-21-probility)
add_subdirectory(mock_problems)
add_subdirectory(chapter6-minimumm-weight-tree)
add_subdirectory(chapter4_shortest_path)
add_subdirectory(chapter9-critical-links)
add_subdirectory(chapter12_dp_1)



set(SOURCE_FILES post_office_1160.cpp)
add_executable(POJSolutions ${SOURCE_FILES})