//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_BISHOP_H_
#define CONSOLE_CHESS_PAWNS_BISHOP_H_
#include "piece.h"

class Bishop : public Piece {
public:
  Bishop() { info_ = P_BLACK; }

  explicit Bishop(char color) { info_ = color; }

  Bishop(const Bishop &other) = default;
  double Value() const override {
    if (Color())
      return 3.5;
    else
      return -3.5;
  }

  static bool Empty() { return false; }

  explicit operator char() const override {
    if (Color())
      return 'b';
    else
      return 'B';
  }

  void GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                std::array<Move, 27> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_BISHOP_H_
