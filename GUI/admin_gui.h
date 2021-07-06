//
// Created by studio25 on 06.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_ADMIN_GUI_H_
#define CONSOLE_CHESS_GUI_ADMIN_GUI_H_

#include "chess_board_gui.h"
#include <SDL_main.h>
#include <chess_board.h>

class AdminGui {

  ChessBoard game_;
  ChessBoardGui console_handle_;
};

#endif // CONSOLE_CHESS_GUI_ADMIN_GUI_H_
