cmake_minimum_required(VERSION 3.18)
project(os4)

set(CMAKE_CXX_STANDARD 14)

add_executable(os4 main.cpp block.h storage_manager.cpp storage_manager.h files.h benchmark.h)
