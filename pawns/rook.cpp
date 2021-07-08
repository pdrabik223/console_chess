//
// Created by studio25 on 18.06.2021.
//

#include "rook.h"
#include <vector>

void Rook::GenMoves(std::array<Piece *, 64> &board, unsigned int position,
                    std::vector<Move> &possible_moves) {
  /// the x part of position
  const int px = position / B_WIDTH;
  /// the y part of position
  const int py = position % B_WIDTH;

  unsigned last_move = 0;


  for (int z = px + 1; z < 8; ++z) { // up
    if (AddMove(board, possible_moves, Color(), position, z * 8 + py))
      break;
  }

  for (int z = px - 1; z >= 0; --z) { // down
    if (AddMove(board, possible_moves, Color(), position, z * 8 + py))
      break;
  }

  for (int z = py + 1; z < 8; ++z) { // right
    if (AddMove(board, possible_moves, Color(), position, px * 8 + z))
      break;
  }

  for (int z = py - 1; z >= 0; --z) { // left
    if (AddMove(board, possible_moves, Color(), position, px * 8 + z))
      break;
  }
}
bool Rook::IsEmpty() { return false; }
bool Rook::Color() const { return info_ bitand 1; }
bool Rook::Moved() const { return info_ bitand 2; }
void Rook::SetMoved() { info_ |= 2; }
PieceType Rook::GetPieceType() { return Color() ? WHITE_ROOK : BLACK_ROOK; }
