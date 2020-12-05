cmake_minimum_required(VERSION 3.10)
project(AdventOfCode2020)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(day5)
