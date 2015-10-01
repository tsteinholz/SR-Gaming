cmake_minimum_required(VERSION 3.3)
project(MiniProject1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SOURCE_FILES main.cpp)
add_executable(MiniProject1 ${SOURCE_FILES})

find_package(Allegro)
message("compiling with version ${allegro_VERSION}")
include_directories(${allegro_INCLUDE_DIRS})
target_link_libraries(MiniProject1 ${allegro_LIBRARY_DIRS})
