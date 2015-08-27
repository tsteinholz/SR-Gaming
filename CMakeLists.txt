cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(HelloWorld_CPP_SRHS)

set(HW_SOURCE_FILES
    SRHS/HelloWorld/main.cpp
    )

add_executable(HelloWorld_CPP_SRHS ${SOURCE_FILES})

project(RandProgram)

set(Rand_SOURCE_FILES

    )

add_executable(Rand_SOURCE_FILES RandProgram)