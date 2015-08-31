cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(HelloWorld_CPP_SRHS)

set(HW_SOURCE_FILES
    SRHS/HelloWorld/main.cpp
    )

add_executable(HelloWorld_CPP_SRHS ${SOURCE_FILES})