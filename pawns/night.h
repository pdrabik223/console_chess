//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_NIGHT_H_
#define CONSOLE_CHESS_PAWNS_NIGHT_H_
#include "piece.h"
class Night : public Piece {
public:
  Night() { info_ = P_BLACK; }

  explicit Night(char color) { info_ = color; }

  double Value() const override {
    if (Color())
      return 3;
    else
      return -3;
  }

  Night(const Night &other) = default;

  static bool Empty() { return false; }

  explicit operator char() const override { return 'n'; }

  void GenMoves(std::array<Piece *, 64> &board, const unsigned int position,
                std::array<Move, 27> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_NIGHT_H_
