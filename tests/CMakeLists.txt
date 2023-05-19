cmake_minimum_required(VERSION 3.10)

project(TheFloors)
set(CMAKE_CXX_STANDARD 20)

set(WORK_DIR ..)

set(SOURCE_FILES engine/utils/test_timer.cpp)
add_executable(my_tests ${SOURCE_FILES})

target_include_directories(my_tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_directories(my_tests PRIVATE ${GTEST_LIBS_DIR})
target_link_libraries(my_tests PRIVATE ${GTEST_LIBS} -lgtest)

add_test(NAME my_tests COMMAND my_tests)
