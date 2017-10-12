cmake_minimum_required(VERSION 3.2)
project(FilterApp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Filter.h Kernel.h PPMImage.h)
add_executable(FilterApp ${SOURCE_FILES} )