cmake_minimum_required(VERSION 3.3)
project(MiniProject1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(SOURCE_FILES main.cpp)
add_executable(MiniProject1 ${SOURCE_FILES})

#find_package(Allegro5)
#include_directories(${ALLEGRO5_INCLUDE_DIR})
#target_link_libraries(MiniProject1 ${ALLEGRO5_LIBRARIES})

#find_package(allegro 5.1 COMPONENTS main image primative color)
#message("Building with Allegro version {$allegro_VERSION}")
#include_directories(${allegro_INCLUDE_DIRS})
#target_link_libraries(MiniProject1 ${allegro_LIBRARIES})

include_directories(include)
target_link_libraries(MiniProject1 lib)