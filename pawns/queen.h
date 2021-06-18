//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_QUEEN_H_
#define CONSOLE_CHESS_PAWNS_QUEEN_H_
#include "piece.h"
class Queen : public Piece {
public:
  Queen() { info_ = P_BLACK; }

  explicit Queen(char color) { info_ = color; }

  Queen(const Queen &other) = default;

  double Value() const override {
    if (Color())
      return 9;
    else
      return -9;
  }

  static bool Empty() { return false; }

  explicit operator char() const override { return 'q'; }

  void GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                std::array<Move, 27> &possible_moves) override;
};


#endif // CONSOLE_CHESS_PAWNS_QUEEN_H_
