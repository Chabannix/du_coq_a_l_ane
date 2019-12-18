cmake_minimum_required(VERSION 3.13)
project(du_coq_a_l_ane C)

file(GLOB SRC_C "src/*.c")

set(CMAKE_C_STANDARD 11)

add_executable(exe ${SRC_C})
target_compile_options(exe PRIVATE -Wall -g)