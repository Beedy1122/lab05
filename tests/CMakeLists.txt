cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(testss)

enable_testing()

add_executable(testion test1.cpp)

target_link_libraries(testion banking gtest gmock)
add_test(tests_lab5 testion)
