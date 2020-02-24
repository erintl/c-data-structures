cmake_minimum_required(VERSION 3.15)
project(c_data_structures C)

set(CMAKE_C_STANDARD 99)

add_executable(c_data_structures main.c source/stack.c header/stack.h source/stack_examples.c header/stack_examples.h header/list.h source/list.c)