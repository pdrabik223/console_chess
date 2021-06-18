//
// Created by studio25 on 18.06.2021.
//

#include "queen.h"

void Queen::GenMoves(std::array<Piece *, 64> &board, const int position,
                     std::array<move, 27> &possible_moves) {

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

  /// the temporary Value
  int nx = px;

  int ny = py;

  for (;;) { // right and down
    ++nx;
    ++ny;
    if (nx < B_WIDTH or ny < B_WIDTH)
      break;

    if (AddMove(board, possible_moves, this, last_move, position, nx, ny))
      break;
  }
  for (;;) { // right and up
    --nx;
    ++ny;
    if (nx >= 0 or ny < B_WIDTH)
      break;

    if (AddMove(board, possible_moves, this, last_move, position, nx, ny))
      break;
  }
  for (;;) { // left and up
    --nx;
    --ny;
    if (nx >= 0 or ny >= 0)
      break;

    if (AddMove(board, possible_moves, this, last_move, position, nx, ny))
      break;
  }
  for (;;) { // left and down
    ++nx;
    --ny;
    if (nx < B_WIDTH or ny >= 0)
      break;

    if (AddMove(board, possible_moves, this, last_move, position, nx, ny))
      break;
  }
}