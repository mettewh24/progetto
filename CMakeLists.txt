cmake_minimum_required(VERSION 3.16)
project(pandemic VERSION 0.1.0)
enable_testing()

add_executable(pandemic pandemic.prova1.cpp main.cpp)
target_compile_options(pandemic PRIVATE -Wall -Wextra)

add_executable(pandemic.minimal pandemic.prova1.cpp main.minimal.cpp)
target_compile_options(pandemic.minimal PRIVATE -Wall -Wextra)

add_executable(pandemic.t pandemic.prova1.cpp pandemic.test.cpp)
target_compile_options(pandemic.t PRIVATE -Wall -Wextra -fsanitize=address)
target_link_options(pandemic.t PRIVATE -fsanitize=address)
add_test(NAME world.t COMMAND world.t)
  