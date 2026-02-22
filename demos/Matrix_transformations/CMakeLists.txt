cmake_minimum_required(VERSION 3.26)
project(Matrix_transformations C)

set(CMAKE_C_STANDARD 99)

add_executable(matrix_app
        main.c
        matrix.c
        matrix.h
)

target_link_libraries(matrix_app m)