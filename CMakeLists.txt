cmake_minimum_required(VERSION 3.9)
project(SunServer CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

add_subdirectory(src/app)
add_subdirectory(src/domain)

file (GLOB src_files "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(SunServer ${src_files})