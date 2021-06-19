//
// Created by studio25 on 18.06.2021.
//

#include "pawn.h"

/// i've got new rule
/// NEVER TEST ANYTHING
/// that's what lammers do
/// AND WE ARE PR06RAMM3R5

void Pawn::GenMoves(std::array<Piece *, 64> &board, const unsigned int position,
                    std::array<Move, 27> &possible_moves) {
  possible_moves.fill({0, 0});

  if (Color() == P_BLACK) {
    GenMovesForBlack(board, position, possible_moves);
  } else {
    GenMovesForWhite(board, position, possible_moves);
  }
}
void Pawn::GenMovesForBlack(std::array<Piece *, 64> &board,
                            const unsigned int position,
                            std::array<Move, 27> &possible_moves) {
  unsigned last_move = 0;

  if (board[position + B_WIDTH]->IsEmpty())
    possible_moves[last_move] = {position, position + B_WIDTH};
  last_move++;

  if (!board[position + B_WIDTH - 1]->IsEmpty() and
      !board[position + B_WIDTH - 1]) {
    possible_moves[last_move] = {position, position + B_WIDTH - 1};
    last_move++;
  }
  if (!board[position + B_WIDTH + 1]->IsEmpty() and
      !board[position + B_WIDTH + 1]) {
    possible_moves[last_move] = {position, position + B_WIDTH + 1};
    last_move++;
  }
  if (!Moved()) {
    possible_moves[last_move] = {position, position + B_WIDTH * 2};
  }
}
void Pawn::GenMovesForWhite(std::array<Piece *, 64> &board,
                            const unsigned int position,
                            std::array<Move, 27> &possible_moves) {
  unsigned last_move = 0;
  if (board[position - B_WIDTH]->IsEmpty())
    possible_moves[last_move] = {position, position - B_WIDTH};
  last_move++;

  if (!board[position - B_WIDTH - 1]->IsEmpty() and
      board[position - B_WIDTH - 1]) {
    possible_moves[last_move] = {position, position - B_WIDTH - 1};
    last_move++;
  }
  if (!board[position - B_WIDTH + 1]->IsEmpty() and
      board[position - B_WIDTH + 1]) {
    possible_moves[last_move] = {position, position - B_WIDTH + 1};
    last_move++;
  }

  if (!Moved()) {
    possible_moves[last_move] = {position, position - B_WIDTH * 2};
    last_move++;
  }
}
