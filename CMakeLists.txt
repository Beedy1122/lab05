cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(--coverage)
add_link_options(--coverage)

project(itog)

add_subdirectory(third-party/gtest)
add_subdirectory(banking)
add_subdirectory(tests)
