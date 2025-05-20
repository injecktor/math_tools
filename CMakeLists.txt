cmake_minimum_required(VERSION 3.22)
project(math_tools)

set(CMAKE_CXX_STANDARD 20)

add_executable(math_tools 
        main.cpp
        math_tools.hpp
        common.cpp
        hashes.cpp
)

target_include_directories(math_tools PRIVATE 
        ${CMAKE_CURRENT_DIR}
)