cmake_minimum_required(VERSION 3.16)
project(pandemic VERSION 0.1.0)

add_executable(pandemic main.cpp)
target_compile_options(pandemic PRIVATE -Wall -Wextra)