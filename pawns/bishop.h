//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_BISHOP_H_
#define CONSOLE_CHESS_PAWNS_BISHOP_H_
#include "piece.h"
#include <vector>

class Bishop : public Piece {
public:
  Bishop() { info_ = P_BLACK; }

  explicit Bishop(bool color) {
    if (color)
      info_ = 1;
    else
      info_ = 0;
  }

  Bishop(const Bishop &other) = default;

  double Value() const override {
    if (Color())
      return 3.5;
    else
      return -3.5;
  }

  virtual Bishop *Clone() { return new Bishop(*this); };
  bool IsEmpty() override;
  bool Color() const override;
  bool Moved() const override;
  void SetMoved() override;
  PieceType GetPieceType() override;

  explicit operator char() const override {
    if (Color())
      return 'b';
    else
      return 'B';
  }
  unsigned char Hash() const { if(Color()) return 3; else return 9;};

  void GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                std::vector<Move> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_BISHOP_H_
