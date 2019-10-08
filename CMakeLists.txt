cmake_minimum_required(VERSION 3.13)
project(print-in-order)

find_package( Threads )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(print-in-order-condition-variables main-condition-variables.cpp)
target_compile_options(print-in-order-condition-variables PRIVATE -Wall -Wextra -pedantic -O3)
target_link_libraries(print-in-order-condition-variables Threads::Threads)

add_executable(print-in-order-atomic main-atomic.cpp)
target_compile_options(print-in-order-atomic PRIVATE -Wall -Wextra -pedantic -O3)
target_link_libraries(print-in-order-atomic Threads::Threads)

add_executable(print-in-order-two-atomic-bools main-two-atomic-bools.cpp)
target_compile_options(print-in-order-two-atomic-bools PRIVATE -Wall -Wextra -pedantic -O3)
target_link_libraries(print-in-order-two-atomic-bools Threads::Threads)

