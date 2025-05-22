cmake_minimum_required(VERSION 3.22)
project(math_tools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_library(math_tools STATIC
        math_tools.hpp
        common.cpp
        hashes.cpp
)

target_include_directories(math_tools PRIVATE 
        ${CMAKE_CURRENT_DIR}
)