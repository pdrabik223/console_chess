//
// Created by studio25 on 18.06.2021.
//

#include "queen.h"
#include <vector>

void Queen::GenMoves(std::array<Piece *, 64> &board,
                     unsigned int position,
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

  /// the temporary Value
  int nx = px;
  int ny = py;

  for (;;) { // right and down
    ++nx;
    ++ny;
    if (nx == B_WIDTH or ny == B_WIDTH)
      break;

    if (AddMove(board, possible_moves, Color(), position, nx * 8 + ny))
      break;
  }
  nx = px;
  ny = py;
  for (;;) { // right and up
    --nx;
    ++ny;
    if (nx < 0 or ny == B_WIDTH)
      break;

    if (AddMove(board, possible_moves, Color(), position, nx * 8 + ny))

      break;
  }
  nx = px;
  ny = py;
  for (;;) { // left and up
    --nx;
    --ny;
    if (nx < 0 or ny < 0)
      break;

    if (AddMove(board, possible_moves, Color(), position, nx * 8 + ny))
      break;
  }
  nx = px;
  ny = py;
  for (;;) { // left and down
    ++nx;
    --ny;
    if (nx == B_WIDTH or ny < 0)
      break;

    if (AddMove(board, possible_moves, Color(), position, nx * 8 + ny))
      break;
  }
}
bool Queen::IsEmpty() { return false; }
bool Queen::Color() const { return info_ bitand 1; }
bool Queen::Moved() const { return info_ bitand 2; }
void Queen::SetMoved() { info_ |= 2; }
unsigned char Queen::Hash() { if(Color()) return 5; else return 11; }
