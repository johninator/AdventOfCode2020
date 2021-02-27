cmake_minimum_required(VERSION 3.0.0)
project(day8 LANGUAGES CXX VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(day8_1 part1.cpp)
add_executable(day8_2 part2.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
