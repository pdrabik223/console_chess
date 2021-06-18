cmake_minimum_required(VERSION 3.19)
project(console_chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

set(PAWNS
        pawns/piece.h pawns/piece.cpp
        pawns/pawn.h pawns/pawn.cpp
        pawns/bishop.h pawns/bishop.cpp
        pawns/rook.h pawns/rook.cpp
        pawns/night.h pawns/night.cpp
        pawns/queen.h pawns/queen.cpp
        pawns/king.h pawns/king.cpp
        )

add_executable(admin admin_chess.cpp
        chess_board.h chess_board.cpp

        move.h move.cpp


        ${PAWNS}
       )
