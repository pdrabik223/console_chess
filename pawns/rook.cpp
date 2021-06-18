//
// Created by studio25 on 18.06.2021.
//

#include "rook.h"

void Rook::GenMoves(std::array<Piece *, 64> &board, const unsigned int position,
                    std::array<Move, 27> &possible_moves) {
  /// the x part of position
  const int px = position / B_WIDTH;
  /// the y part of position
  const int py = position % B_WIDTH;

  unsigned last_move = 0;
  possible_moves.fill({0, 0});

  for (int z = px + 1; z < 8; ++z) { // up
    if (AddMove(board, possible_moves, this, last_move, position, z, py))
      break;
  }

  for (int z = px - 1; z >= 0; --z) { // down
    if (AddMove(board, possible_moves, this, last_move, position, z, py))
      break;
  }

  for (int z = py + 1; z < 8; ++z) { // right
    if (AddMove(board, possible_moves, this, last_move, position, px, z))
      break;
  }

  for (int z = py - 1; z >= 0; --z) { // left
    if (AddMove(board, possible_moves, this, last_move, position, px, z))
      break;
  }
}


