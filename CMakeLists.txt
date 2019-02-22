cmake_minimum_required(VERSION 3.13)
project(Solitaire)

set(CMAKE_CXX_STANDARD 14)

add_executable(Solitaire Solitaire.cpp Card.cpp Deck.cpp Gameboard.cpp Card.h Deck.h Gameboard.h)