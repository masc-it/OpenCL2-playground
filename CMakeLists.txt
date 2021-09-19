cmake_minimum_required(VERSION 3.16)
project(opencltest)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O2 -Wall")

file(GLOB CL_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/kernels/*.cl)
file(GLOB CL_HEADERS  ${CMAKE_CURRENT_SOURCE_DIR}/kernels/*.h)
set(CMAKE_CXX_STANDARD 11)
set(USE_CL1_HPP 1)

include_directories(${OCL_PATH})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

find_path(OCL_PATH CL/cl2.hpp)
find_library(OCL_LIB OpenCL)
configure_file(config.cmake.hpp config.hpp)

add_executable(opencltest src/main.cpp include/opencl_include.h include/opencl_utils.hpp src/opencl_utils.cpp )
target_link_libraries(opencltest OpenCL)
