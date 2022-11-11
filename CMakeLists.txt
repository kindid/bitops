cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# split these - actually put the test somewhere else
# also, don't forget there's some insanity with node
# getting node to use the CMAKE CC settings would be wise
project(bits)

message("${SOMEVARIABLE}")

file(GLOB COMPILER_TESTS_PASS compiler_tests/pass/*.cpp)
file(GLOB COMPILER_TESTS_FAIL compiler_tests/fail/*.cpp)
#list(JOIN COMPILER_TESTS "\n" JOINED_COMPILER_TESTS)
#message(${JOINED_COMPILER_TESTS})

#enable_testing()

include(GoogleTest)
include(CTest)

#include_directories(thirdparty/wise_enum-master)

set(GTEST ${PROJECT_SOURCE_DIR}/3rd/googletest)

#add_library(bits STATIC bits.cpp)


add_subdirectory(${GTEST})
#add_executable(bitops_tst bitops.cpp bitops_tst.cpp bitops.h bits.h here.h)
add_executable(bitops_tst bits_test.cpp bits.h here.h here.cpp)
include_directories(bitops_tst ${GTEST}/googletest/include)
target_link_directories(bitops_tst PUBLIC ${GTEST}/build/lib)
target_link_libraries(bitops_tst gtest)
target_link_libraries(bitops_tst gtest_main)

# this is the one you want.
#message("${CMAKE_CXX_COMPILER}")
#message("${CMAKE_CURRENT_BINARY_DIR}")
#message("${CMAKE_CURRENT_SOURCE_DIR}")

#    message("CT is ${CT}")
#    message(${BLAH})

foreach(COMPILER_TEST ${COMPILER_TESTS_PASS})
    cmake_path(GET COMPILER_TEST FILENAME COMPILER_TEST_FILENAME)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/compiler_test_pass)
    add_test(
        NAME ${COMPILER_TEST_FILENAME}_PASS
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/compiler_test_pass"
        COMMAND node "${CMAKE_CURRENT_SOURCE_DIR}/compiler_tests/test_compiler_test.js" ${COMPILER_TEST} pass)
endforeach()

foreach(COMPILER_TEST ${COMPILER_TESTS_FAIL})
    cmake_path(GET COMPILER_TEST FILENAME COMPILER_TEST_FILENAME)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/compiler_test_fail)
    add_test(
        NAME ${COMPILER_TEST_FILENAME}_FAIL
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/compiler_test_fail"
        COMMAND node "${CMAKE_CURRENT_SOURCE_DIR}/compiler_tests/test_compiler_test.js" ${COMPILER_TEST} fail)
endforeach()

gtest_add_tests(bitops_tst "" AUTO)

# make this a macro/fn plz.
# set the compiler
# set the output folder *possibly*
# probably generate the c includes - because
# test for errors - no c includes if errors
#add_test(
#    NAME trytest
#    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/compiler_tests"
#    COMMAND node "${CMAKE_CURRENT_SOURCE_DIR}/compiler_tests/test_compiler_test.js" abc def ghi blah)
