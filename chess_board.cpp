//
// Created by pc on 23.04.2021.
//
// todo if windows defined console output must change
//
#include "chess_board.h"
#include <Windows.h>
#include <vector>

ChessBoard::ChessBoard(const ChessBoard &other) { plane_ = other.plane_; }

ChessBoard::ChessBoard() {

  plane_[0] = new Rook(P_BLACK);
  plane_[1] = new Night(P_BLACK);
  plane_[2] = new Bishop(P_BLACK);
  plane_[3] = new Queen(P_BLACK);
  plane_[4] = new King(P_BLACK);
  plane_[5] = new Bishop(P_BLACK);
  plane_[6] = new Night(P_BLACK);
  plane_[7] = new Rook(P_BLACK);
  for (int i = 8; i < 16; ++i)
    plane_[i] = new Pawn(P_BLACK);

  for (int i = 16; i < 48; ++i)
    plane_[i] = new Piece();

  for (int i = 48; i < 56; ++i)
    plane_[i] = new Pawn(P_WHITE);

  plane_[56] = new Rook(P_WHITE);
  plane_[57] = new Night(P_WHITE);
  plane_[58] = new Bishop(P_WHITE);
  plane_[59] = new Queen(P_WHITE);
  plane_[60] = new King(P_WHITE);
  plane_[61] = new Bishop(P_WHITE);
  plane_[62] = new Night(P_WHITE);
  plane_[63] = new Rook(P_WHITE);
}

unsigned ChessBoard::Size() { return 64; }

ChessBoard &ChessBoard::operator=(const ChessBoard &other) {
  if (&other == this)
    return *this;
  plane_ = other.plane_;
  return *this;
}

Piece *&ChessBoard::operator[](unsigned int position) {
  return plane_[position];
}

Piece &ChessBoard::GetElement(unsigned int x, unsigned int y) {
  return *plane_[x * B_WIDTH + y];
}

double ChessBoard::EvaluatePosition() {

  double weight_of_move = 0.1;
  std::vector<Move> white_move_buffer;
  std::vector<Move> black_move_buffer;
  double eva = 0.0;

  for (int i = 0; i < 64; i++) {



    if (plane_[i]->Color()) {

    white_move_buffer.reserve( white_move_buffer.size() + 27);
      plane_[i]->GenMoves(plane_, i, white_move_buffer);

    } else {
      black_move_buffer.reserve( black_move_buffer.size() + 27);

      plane_[i]->GenMoves(plane_, i, black_move_buffer);
    }

    eva += plane_[i]->Value();
  }
  eva+= black_move_buffer.size() * weight_of_move;
  eva-= black_move_buffer.size() * weight_of_move;

  return eva;
}

Piece &ChessBoard::GetElement(unsigned int position) {
  return *plane_[position];
}
void ChessBoard::DoMove(const Move &target) {

  *plane_[target.to_] = *plane_[target.from_];
  plane_[target.to_]->SetMoved();
  delete plane_[target.from_];
  plane_[target.from_] = new Piece();
}



/// todo debate over it
void ChessBoard::GenAllPossibleMoves(bool color,
                                     std::vector<Move> &possible_moves) {

  for (int i = 0; i < plane_.size(); i++) {
    if (plane_[i]->Color() == color) {

      possible_moves.reserve(possible_moves.size() + 27);

      plane_[i]->GenMoves(plane_, i, possible_moves);

    }
  }
}
void ChessBoard::EvaluateMove(Move &target) {
  auto temp_board(*this);
  temp_board.DoMove(target);
  target.evaluation_ = temp_board.EvaluatePosition();
}
