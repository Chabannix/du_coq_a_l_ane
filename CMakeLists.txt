cmake_minimum_required(VERSION 3.13)
project(du_coq_a_l_ane C)

set(CMAKE_C_STANDARD 11)

add_executable(exe src/main.c)
target_compile_options(exe PRIVATE -Wall -g)