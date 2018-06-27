cmake_minimum_required(VERSION 3.5)
project(SunServer CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

file (GLOB src_files "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(SunServer "${src_files}")
