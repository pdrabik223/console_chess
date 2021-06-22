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
  void DisplayBestMoves(std::vector<Move> &move_buffer, bool color);

  void MakeEmFight(std::vector<int> settings);

  ChessBoard game_;
  Scml console_handle_;
  void Load();
};

#endif // CONSOLE_CHESS_WINDOWS_CONSOLE_ADMIN_H_
