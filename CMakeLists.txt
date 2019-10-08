cmake_minimum_required(VERSION 3.13)
project(print-in-order)

find_package( Threads )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(print-in-order main.cpp)
target_compile_options(print-in-order PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(print-in-order Threads::Threads)
