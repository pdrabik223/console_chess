cmake_minimum_required(VERSION 3.19)
project(console_chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(admin admin_chess.cpp
        chess_board.h chess_board.cpp
        pawns/piece.h pawns/piece.cpp
        move.h move.cpp pawns/queen.cpp pawns/queen.h pawns/night.cpp pawns/night.h pawns/rook.cpp pawns/rook.h pawns/bishop.cpp pawns/bishop.h pawns/pawn.cpp pawns/pawn.h)
