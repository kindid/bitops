
project(compiler_tests)

file(GLOB COMPILER_TESTS_PASS pass/*.cpp)
file(GLOB COMPILER_TESTS_FAIL fail/*.cpp)

foreach(COMPILER_TEST ${COMPILER_TESTS_PASS})
    cmake_path(GET COMPILER_TEST FILENAME COMPILER_TEST_FILENAME)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/compiler_test_pass)
    add_test(
        NAME ${COMPILER_TEST_FILENAME}_PASS
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/compiler_test_pass"
        COMMAND node "${CMAKE_CURRENT_SOURCE_DIR}/test_compiler_test.js" ${COMPILER_TEST} pass)
endforeach()

foreach(COMPILER_TEST ${COMPILER_TESTS_FAIL})
    cmake_path(GET COMPILER_TEST FILENAME COMPILER_TEST_FILENAME)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/compiler_test_fail)
    add_test(
        NAME ${COMPILER_TEST_FILENAME}_FAIL
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/compiler_test_fail"
        COMMAND node "${CMAKE_CURRENT_SOURCE_DIR}/test_compiler_test.js" ${COMPILER_TEST} fail)
endforeach()
