cmake_minimum_required(VERSION 3.3)
project(Nim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Game.h
    main.cpp
    Nim.cpp
    Nim.h
    Utils.h)

add_executable(Nim ${SOURCE_FILES})