//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_PAWN_H_
#define CONSOLE_CHESS_PAWNS_PAWN_H_
#include "piece.h"
class Pawn : public Piece {
public:
  Pawn() { info_ = P_BLACK; }

  explicit Pawn(char color) { info_ = color; }

  Pawn(const Pawn &other) = default;

  double Value() const override {
    if (Color())
      return 1;
    else
      return -1;
  }

  static bool Empty() { return false; }

  explicit operator char() const override {
    if (Color())
      return 'p';
    else
      return 'P';
  }
  virtual Pawn *Clone(){return new Pawn(* this);};

  void GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                std::array<Move, 27> &possible_moves) override;

protected:
  void GenMovesForBlack(std::array<Piece *, 64> &board,
                        const unsigned int position,
                        std::array<Move, 27> &possible_moves) override;
  void GenMovesForWhite(std::array<Piece *, 64> &board,
                        const unsigned int position,
                        std::array<Move, 27> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_PAWN_H_
