cmake_minimum_required(VERSION 3.19)
project(console_chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

# add SDL lib
add_subdirectory(SDL/)
include_directories("./SDL/include")

set(PAWNS
        pawns/piece.h pawns/piece.cpp
        pawns/pawn.h pawns/pawn.cpp
        pawns/bishop.h pawns/bishop.cpp
        pawns/rook.h pawns/rook.cpp
        pawns/night.h pawns/night.cpp
        pawns/queen.h pawns/queen.cpp
        pawns/king.h pawns/king.cpp
       )

set(WIN_CONSOLE
        windows_console/icon.h windows_console/icon.cpp
        windows_console/win_colors.h windows_console/win_colors.cpp
        windows_console/scml.cpp windows_console/scml.h
        windows_console/full_command.cpp windows_console/full_command.h)

set(GUI
        gui/chess_board_gui.h gui/chess_board_gui.cpp)

add_executable(admin
        executables/admin_chess.cpp
        chess_board.h chess_board.cpp
        move.h move.cpp
        ${PAWNS}
        ${WIN_CONSOLE}
        windows_console/admin.cpp windows_console/admin.h)

add_executable(admin_gui
        executables/admin_chess_gui.cpp
        chess_board.h chess_board.cpp
        move.h move.cpp
        ${PAWNS}
        gui/chess_board_gui.h gui/chess_board_gui.cpp
        gui/admin_gui.h gui/admin_gui.cpp)


target_link_libraries(admin
        SDL2
        SDL2::SDL2main)

target_link_libraries(admin_gui
        SDL2
        SDL2::SDL2main)

if (WIN32)
    set(SDL_SHARED SDL2d.dll)
endif (WIN32)
if (UNIX)
    set(SDL_SHARED libSDL2d.so)
endif (UNIX)