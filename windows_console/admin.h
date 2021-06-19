//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_WINDOWS_CONSOLE_ADMIN_H_
#define CONSOLE_CHESS_WINDOWS_CONSOLE_ADMIN_H_

#include "chess_board.h"
#include <vector>
#include <windows_console/scml.h>
#include "full_command.h"

class Admin {
public:
  Admin();

private:
  void MinMaxAll(int depth, bool color);
  void MinMax(int depth, int position);
  void Help();
  void ShowPossible();
  void ShowPossible(int position);
  void AddPiece(full_command input);

  ChessBoard game_;
  Scml console_handle_;
};

#endif // CONSOLE_CHESS_WINDOWS_CONSOLE_ADMIN_H_
