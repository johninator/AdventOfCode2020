cmake_minimum_required(VERSION 3.0.0)
project(day17 LANGUAGES CXX VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(day17_1 part1.cpp)
add_executable(day17_2 part2.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
