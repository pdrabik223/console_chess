//
// Created by pc on 23.04.2021.
//

#include "pawns/piece.h"

bool AddMove(std::array<Piece *, 64> &board, std::vector<Move> &possible_moves,
             bool color, const unsigned position, unsigned int target) {

  if (board[target]->IsEmpty()) {
    possible_moves.emplace_back(position, target);

  } else if (board[target]->Color() not_eq color) {
	possible_moves.emplace_back(position, target);
    return true;

  } else return true;

  return false;
}
unsigned CCord(const unsigned int &x, const unsigned int &y) { return x * B_WIDTH + y; }
