cmake_minimum_required(VERSION 3.13)
project(du_coq_a_l_ane C)

set(CMAKE_C_STANDARD 11)

set(SRC
    src/main.c
    src/data.h
    src/dico.h
    src/word.h
    src/graphe.h
    src/dijkstra.h
    )

add_executable(exe ${SRC})
target_compile_options(exe PRIVATE -Wall -g)