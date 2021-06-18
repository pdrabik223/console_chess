//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_PIECE_H_
#define CONSOLE_CHESS_PAWNS_PIECE_H_

#include "move.h"
#include <array>
#include <iostream>

#define BLACK 0
#define WHITE 1

#define B_HEIGHT 8
#define B_WIDTH 8



class Piece {

public:
  Piece() : info_(BLACK) {}

  Piece(const Piece &other) = default;

  virtual explicit operator char() const { return ' '; }

  static bool IsEmpty() { return true; }

  /// \return true if white
  /// \return false if black
  bool Color() const { return info_ bitand 1; }

  bool Moved() const { return info_ bitand 2; }

  virtual double Value() const { return 0.0; }

  virtual void GenMoves(std::array<Piece *, 64> &board, const int position,
                        std::array<move, 27> &possible_moves) {
    possible_moves.fill({0, 0});
  };

protected:
  /// to save space and copy time, and we will do a lot of copying
  /// we use flag system
  /// least significant bit: colour
  /// black 0 white 1
  /// next if Moved
  /// 1 Moved 0 if not
  unsigned char info_;
};


bool AddMove(std::array<Piece *, 64> &board,
             std::array<move, 27> &possible_moves, Piece *me,
             unsigned &last_move, const int &position,  int x,
              int y);

#endif // CONSOLE_CHESS_PAWNS_PIECE_H_
