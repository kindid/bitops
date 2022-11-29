cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(kindid_bitops)

enable_testing()

set(GTEST ${PROJECT_SOURCE_DIR}/3rd/googletest)

add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(here)
add_subdirectory(${GTEST})
add_subdirectory(test)

