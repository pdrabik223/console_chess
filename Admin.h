//
// Created by studio25 on 24.07.2021.
//

#ifndef CONSOLE_CHESS__ADMIN_H_
#define CONSOLE_CHESS__ADMIN_H_

#include "chess_board.h"
#include "move.h"
#include <vector>
#include <windows_console/full_command.h>
class Admin {
protected:
  virtual Move MinMaxAll(int depth, bool color, int threads) = 0;
  virtual void MinMax(int depth, int position, int threads) = 0;

  virtual Move AlfaBetaMinMaxAll(int depth, bool color, int threads) = 0;
  virtual void AlfaBetaMinMax(int depth, int position, int threads) = 0;

  virtual Move AlfaBetaMinMaxWTranspositionTableAll(int depth, bool color, int threads) = 0;
  virtual void AlfaBetaMinMaxWTranspositionTable(int depth, int position, int threads) = 0;

  virtual void Help() = 0;

  virtual void ShowPossible() = 0;
  virtual void ShowPossible(int position) = 0;

  virtual void DisplayMoves( std::vector<Move> &move_buffer, bool color) = 0;
  virtual void DisplayBestMoves(std::vector<Move> &move_buffer, bool color) = 0;

  virtual void AddPiece(full_command input) = 0;
  virtual void MakeEmFight(std::vector<int> settings) = 0;

   ChessBoard game_;
  virtual void Load() = 0;

};

#endif // CONSOLE_CHESS__ADMIN_H_
