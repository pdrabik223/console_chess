cmake_minimum_required(VERSION 3.19)
project(console_chess)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

# add SDL lib
add_subdirectory(SDL/)
include_directories(${PROJECT_SOURCE_DIR}/SDL/include)
include_directories(${PROJECT_SOURCE_DIR}/SDL2_ttf/include)


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
        gui/chess_board_gui.h gui/chess_board_gui.cpp
        gui/ppm_loader.cpp
        gui/file_exception.h
        gui/arrow.h gui/arrow.cpp
        gui/circle.h gui/circle.cpp
        gui/button.h gui/button.cpp)

add_executable(admin
        executables/admin_chess.cpp
        chess_board.h chess_board.cpp
        move.h move.cpp
        ${PAWNS}
        ${WIN_CONSOLE}
        Admin.h Admin.cpp
        windows_console/admin_console.cpp windows_console/admin_console.h)

add_executable(admin_gui
        executables/admin_chess_gui.cpp
        chess_board.h chess_board.cpp
        move.h move.cpp
        ${PAWNS}
        ${GUI}
        windows_console/full_command.cpp windows_console/full_command.h
        gui/admin_gui.h gui/admin_gui.cpp)

target_link_libraries(admin_gui
        SDL2
        SDL2::SDL2main
        )

find_library(SDL_TTF SDL2TTF SDL2_TTF SDL_Ttf SDL_ttf SDL2TTF_LIBRARY  REQUIRED PATHS ${PROJECT_SOURCE_DIR}/SDL2_ttf/lib/x64)
target_link_libraries(admin_gui ${SDL_TTF})


if (WIN32)
    set(SDL_SHARED SDL2d.dll)
endif (WIN32)
if (UNIX)
    set(SDL_SHARED libSDL2d.so)
endif (UNIX)