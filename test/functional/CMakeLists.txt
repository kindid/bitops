set(GTEST ${PROJECT_SOURCE_DIR}/3rd/googletest)
#message(${GTEST})

enable_testing()

include(GoogleTest)
include(CTest)

add_executable(bitops_tst bits_test.cpp)

include_directories(bitops_tst ${GTEST}/googletest/include)

target_link_libraries(bitops_tst PUBLIC here)
target_link_libraries(bitops_tst PUBLIC bits)
target_link_directories(bitops_tst PUBLIC ${GTEST}/build/lib)
target_link_libraries(bitops_tst PRIVATE gtest)
target_link_libraries(bitops_tst PRIVATE gtest_main)

gtest_add_tests(bitops_tst "" AUTO)
