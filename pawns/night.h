//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_NIGHT_H_
#define CONSOLE_CHESS_PAWNS_NIGHT_H_
#include "piece.h"
#include <vector>
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

  explicit operator char() const override {
    if (Color())
      return 'n';
    else
      return 'N';
  }

  virtual Night *Clone() { return new Night(*this); };

  bool IsEmpty() override { return false; }
  bool Color() const override { return info_ bitand 1; }
  bool Moved() const override { return info_ bitand 2; }
  void SetMoved() override;
  void GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                std::vector<Move> &possible_moves) override ;

};
#endif // CONSOLE_CHESS_PAWNS_NIGHT_H_
