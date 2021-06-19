//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_ROOK_H_
#define CONSOLE_CHESS_PAWNS_ROOK_H_
#include "piece.h"
class Rook : public Piece {
public:
  Rook() { info_ = P_BLACK; }

  explicit Rook(char color) { info_ = color; }

  double Value() const override {
    if (Color())
      return 5;
    else
      return -5;
  }
  static bool Empty() { return false; }

  explicit operator char() const override {
    if (Color())
      return 'r';
    else
      return 'R';
  }
  virtual Rook *Clone(){return new Rook(* this);};

  void GenMoves(std::array<Piece *, 64> &board, const unsigned int position,
                std::array<Move, 27> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_ROOK_H_
