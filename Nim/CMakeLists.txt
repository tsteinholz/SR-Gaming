cmake_minimum_required(VERSION 3.0)
project(Nim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Game.h
        main.cpp
        Utils.h
        Nim.cpp
        Nim.h
)

add_executable(Nim ${SOURCE_FILES})
