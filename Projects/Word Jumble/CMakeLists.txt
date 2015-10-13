cmake_minimum_required(VERSION 3.3)
project(Word_Jumble)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    word_jumble.cpp)

add_executable(Word_Jumble ${SOURCE_FILES})