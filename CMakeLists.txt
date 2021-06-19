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
        windows_console/scml.cpp windows_console/scml.h)

set(WIN_CONSOLE
        windows_console/icon.h windows_console/icon.cpp
        windows_console/win_colors.h windows_console/win_colors.cpp
        windows_console/scml.cpp windows_console/scml.h
        windows_console/full_command.cpp windows_console/full_command.h)

add_executable(admin executables/admin_chess.cpp
        chess_board.h chess_board.cpp

        move.h move.cpp

        ${PAWNS}
        ${WIN_CONSOLE}
        windows_console/admin.cpp windows_console/admin.h)
