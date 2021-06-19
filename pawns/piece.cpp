//
// Created by pc on 23.04.2021.
//

#include "pawns/piece.h"

bool AddMove(std::array<Piece *, 64> &board,
             std::array<Move, 27> &possible_moves, bool color,
             unsigned &last_move, const unsigned position, unsigned int target) {

  if (board[target]->IsEmpty()) {
    possible_moves[last_move++] = {position, target};

  } else if (board[target]->Color() != color) {
    possible_moves[last_move++] = {position, target};
    return true;

  } else return true;

  return false;
}
unsigned CCord(const unsigned int &x, const unsigned int &y) { return x * B_WIDTH + y; }
