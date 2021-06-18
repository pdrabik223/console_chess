//
// Created by pc on 23.04.2021.
//

#include "pawns/piece.h"


bool AddMove(std::array<Piece *, 64> &board,
              std::array<Move, 27> &possible_moves, Piece *me,
              unsigned last_move, const unsigned position, const int x,
              const int y) {

  if (board[CCord(x, y)]->IsEmpty()) {
    possible_moves[last_move++] = {position, CCord(x, y)};

  } else if (board[CCord(x, y)]->Color() != me->Color()) {
    possible_moves[last_move++] = {position, CCord(x, y)};
    return false;

  } else return false;

  return true;
}
unsigned CCord(const unsigned int &x, const unsigned int &y) { return x * B_WIDTH + y; }
