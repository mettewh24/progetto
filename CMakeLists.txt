cmake_minimum_required(VERSION 3.16)
project(pandemic VERSION 0.1.0)
enable_testing()

add_executable(pandemic pandemic.cpp main.cpp)
target_compile_options(pandemic PRIVATE -Wall -Wextra)

add_executable(pandemic.minimal pandemic.cpp main.minimal.cpp)
target_compile_options(pandemic.minimal PRIVATE -Wall -Wextra)

add_executable(pandemic.t pandemic.cpp pandemic.test.cpp)
target_compile_options(pandemic.t PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(pandemic.t PRIVATE -fsanitize=address)

  