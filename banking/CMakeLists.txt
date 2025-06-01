cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(banking_lib)

add_library(banking STATIC Account.cpp Transaction.cpp)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

