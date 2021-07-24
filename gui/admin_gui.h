//
// Created by studio25 on 06.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_ADMIN_GUI_H_
#define CONSOLE_CHESS_GUI_ADMIN_GUI_H_

#include "chess_board.h"
#include "chess_board_gui.h"
#include <windows_console/full_command.h>

class AdminGui {

public:
  AdminGui();



private:
  Move MinMaxAll(int depth, bool color, int threads);
  void MinMax(int depth, int position, int threads);

  Move AlfaBetaMinMaxAll(int depth, bool color, int threads);
  void AlfaBetaMinMax(int depth, int position, int threads);

  Move AlfaBetaMinMaxWTranspositionTableAll(int depth, bool color, int threads);
  void AlfaBetaMinMaxWTranspositionTable(int depth, int position, int threads);

  void Help();
  void ShowPossible();
  void ShowPossible(int position);
  void AddPiece(full_command input);
  void DisplayMoves( std::vector<Move> &move_buffer, bool color);
  void DisplayBestMoves(std::vector<Move> &move_buffer);

  void MakeEmFight(std::vector<int> settings);

  void Load();

  ChessBoard game_;
  ChessBoardGui gui_handle_;

};

#endif // CONSOLE_CHESS_GUI_ADMIN_GUI_H_
