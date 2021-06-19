//
// Created by studio25 on 18.06.2021.
//

#include "bishop.h"
void Bishop::GenMoves(std::array<Piece *, 64> &board,
                      const unsigned int position,
                      std::array<Move, 27> &possible_moves) {

  /// the x part of position
  const int px = position / B_WIDTH;
  /// the y part of position
  const int py = position % B_WIDTH;

  /// the temporary Value
  int nx = px;

  int ny = py;

  unsigned last_move = 0;
  possible_moves.fill({0, 0});

  for (;;) { // right and down
    ++nx;
    ++ny;
    if (nx < B_WIDTH or ny < B_WIDTH)
      break;

    if (AddMove(board, possible_moves, Color(), last_move, position,
                nx * 8 + ny))
      break;
  }
  for (;;) { // right and up
    --nx;
    ++ny;
    if (nx >= 0 or ny < B_WIDTH)
      break;

    if (AddMove(board, possible_moves, Color(), last_move, position,
                nx * 8 + ny))
      break;
  }
  for (;;) { // left and up
    --nx;
    --ny;
    if (nx >= 0 or ny >= 0)
      break;

    if (AddMove(board, possible_moves, Color(), last_move, position,
                nx * 8 + ny))
      break;
  }
  for (;;) { // left and down
    ++nx;
    --ny;
    if (nx < B_WIDTH or ny >= 0)
      break;

    if (AddMove(board, possible_moves, Color(), last_move, position,
                nx * 8 + ny))
      break;
  }
}
bool Bishop::IsEmpty() { return false; }
bool Bishop::Color() const { return info_ bitand 1; }
bool Bishop::Moved() const { return info_ bitand 2; }
