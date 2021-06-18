//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_KING_H_
#define CONSOLE_CHESS_PAWNS_KING_H_
#include "piece.h"

class King : public Piece {
public:
  King() { info_ = BLACK; }

  explicit King(char color) { info_ = color; }

  King(const King &other) = default;

  double Value() const override {
    if (Color())
      return 999;
    else
      return -999;
  }

  static bool Empty() { return false; }

  explicit operator char() const override { return 'k'; }

  void GenMoves(std::array<Piece *, 64> &board, unsigned position,
                std::array<Move, 27> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_KING_H_

