cmake_minimum_required(VERSION 3.3)
project(HomerTalents)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(HomerTalents ${SOURCE_FILES})