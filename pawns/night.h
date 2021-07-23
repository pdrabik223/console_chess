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

  explicit Night(bool color);

  double Value() const override;

  Night(const Night &other) = default;

  explicit operator char() const override;

  Night *Clone() override { return new Night(*this); };
  unsigned char Hash() const;;
  bool IsEmpty() override { return false; }
  bool Color() const override { return info_ bitand 1; }
  bool Moved() const override { return info_ bitand 2; }
  void SetMoved() override;
  PieceType GetPieceType() override;

  void GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                std::vector<Move> &possible_moves) override;
};
#endif // CONSOLE_CHESS_PAWNS_NIGHT_H_
