cmake_minimum_required(VERSION 3.19)
project(console_chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(admin admin_chess.cpp
        chess_board.h chess_board.cpp
        piece.h piece.cpp
        move.h move.cpp)
