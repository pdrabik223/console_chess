//
// Created by studio25 on 18.06.2021.
//

#include "night.h"

void Night::GenMoves(std::array<Piece *, 64> &board,
                     const unsigned int position,
                     std::array<Move, 27> &possible_moves) {

  /// the x part of position
  const int px = position / B_WIDTH;

  /// the y part of position
  const int py = position % B_WIDTH;

  int nx = px;
  int ny = py;

  unsigned last_move = 0;
  possible_moves.fill({0, 0});

  nx = px - 2; // px -2
  ny = py - 1;
  if (nx >= 0 and ny >= 0)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};

  nx = px - 2;
  ny = py + 1;
  if (nx >= 0 and ny < B_WIDTH)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};

  nx = px + 1;
  ny = py - 2;
  if (nx < B_WIDTH and ny >= 0)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};

  nx = px - 1;
  ny = py - 2;
  if (nx >= 0 and ny >= 0)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};

  nx = px + 1;
  ny = py - 2;
  if (nx < B_WIDTH and ny >= 0)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};

  nx = px - 1;
  ny = py + 2;
  if (nx >= 0 and ny < B_WIDTH)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};

  nx = px + 1;
  ny = py + 2;
  if (nx < B_WIDTH and ny < B_WIDTH)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};

  nx = px + 2; // px -2
  ny = py - 1;
  if (nx < B_WIDTH and ny >= 0)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};

  nx = px + 2;
  ny = py + 1;
  if (nx < B_WIDTH and ny < B_WIDTH)
    if (board[CCord(nx, ny)]->IsEmpty() or
        board[CCord(nx, ny)]->Color() != Color())
      possible_moves[last_move++] = {position, CCord(nx, ny)};
}