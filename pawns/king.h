//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_KING_H_
#define CONSOLE_CHESS_PAWNS_KING_H_
#include "piece.h"
#include <vector>

class King : public Piece {
public:
  King() { info_ = P_BLACK; }

  explicit King(bool color) {
    if (color)
      info_ = 1;
    else
      info_ = 0; }

  King(const King &other) = default;

  double Value() const override {
    if (Color())
      return 1000;
    else
      return -1000;
  }

  explicit operator char() const override {
    if (Color())
      return 'k';
    else
      return 'K';
  }

  virtual King *Clone(){return new King(* this);};
  bool IsEmpty() override;
  bool Color() const override;
  bool Moved() const override;
  void SetMoved() override;

  unsigned char Hash() const { if(Color()) return 6; else return 12;};

  void GenMoves(std::array<Piece *, 64> &board, unsigned position,
                std::vector<Move> &possible_moves) override;
};

#endif // CONSOLE_CHESS_PAWNS_KING_H_
