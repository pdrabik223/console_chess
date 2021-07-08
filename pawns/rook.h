//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_ROOK_H_
#define CONSOLE_CHESS_PAWNS_ROOK_H_
#include "piece.h"
class Rook : public Piece {
public:
  Rook() { info_ = P_BLACK; }

  explicit Rook(bool color) {
    if (color)
      info_ = 1;
    else
      info_ = 0;
  }

  double Value() const override {
    if (Color())
      return 5;
    else
      return -5;
  }

  explicit operator char() const override {
    if (Color())
      return 'r';
    else
      return 'R';
  }
  virtual Rook *Clone() { return new Rook(*this); };
  bool IsEmpty() override;
  bool Color() const override;
  bool Moved() const override;
  void SetMoved() override;
  PieceType GetPieceType() override;
  unsigned char Hash() const { if(Color()) return 4; else return 10;};
  void GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                std::vector<Move> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_ROOK_H_
