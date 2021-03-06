//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_PAWN_H_
#define CONSOLE_CHESS_PAWNS_PAWN_H_
#include "piece.h"
#include <vector>




class Pawn : public Piece {
public:
  Pawn() { info_ = P_BLACK; }

  explicit Pawn(bool color) {
    if (color)
      info_ = 1;
    else
      info_ = 0;
  }

  Pawn(const Pawn &other) = default;

  double Value() const override {
    if (Color())
      return 1;
    else
      return -1;
  }

  explicit operator char() const override {
    if (Color())
      return 'p';
    else
      return 'P';
  }
  virtual Pawn *Clone() { return new Pawn(*this); };

  void GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                std::vector<Move> &possible_moves) override;
  bool IsEmpty() override;
  bool Color() const override;
  bool Moved() const override;
  void SetMoved() override;
  PieceType GetPieceType() override;

  unsigned char Hash() const { if(Color()) return 1; else return 7;};

protected:
  void GenMovesForBlack(std::array<Piece *, 64> &board, unsigned int position,
                        std::vector<Move> &possible_moves) override;
  void GenMovesForWhite(std::array<Piece *, 64> &board, unsigned int position,
                        std::vector<Move> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_PAWN_H_
