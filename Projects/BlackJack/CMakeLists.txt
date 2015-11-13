cmake_minimum_required(VERSION 3.3)
project(BlackJack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#set(SFML_STATIC_LIBRARIES TRUE)

set(SOURCE_FILES
        src/main.cpp
        src/Card.cpp
        src/Deck.cpp
        src/Hand.cpp
        )
add_executable(BlackJack ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR} include)
    target_link_libraries(BlackJack ${SFML_LIBRARIES})
endif ()
