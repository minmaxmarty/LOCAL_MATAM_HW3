cmake_minimum_required(VERSION 3.31)
project(HW3_2425B)

set(CMAKE_CXX_STANDARD 17)

file(GLOB ALL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(HW3_2425B ${ALL_SRC})
