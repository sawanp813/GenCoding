cmake_minimum_required(VERSION 3.18)
project(PS5 C)

set(CMAKE_C_STANDARD 99)

add_executable(PS5 main.c node.c node.h stack.c stack.h rpn.c rpn.h errors.c errors.h converter.c converter.h precedence.c precedence.h)
