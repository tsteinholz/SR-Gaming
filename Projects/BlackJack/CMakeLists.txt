# Probably only works on arch linux with the right packages ;)

cmake_minimum_required (VERSION 3.0.0)
project (BlackJack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable (BlackJack main.cpp Hand.cpp Deck.cpp Card.cpp BlackJack.h BlackJack.cpp)

include_directories (${PROJECT_SOURCE_DIR} /usr/include/allegro5)
link_directories (/usr/lib)
target_link_libraries (BlackJack allegro
                        allegro_acodec
                        allegro_audio
                        allegro_color
                        allegro_font
                        allegro_image
                        allegro_physfs
                        allegro_primitives
                        allegro_ttf)
