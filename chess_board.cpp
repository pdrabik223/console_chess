//
// Created by pc on 23.04.2021.
//
// todo if windows defined console output must change
//
#include "chess_board.h"
#include <Windows.h>
#include <vector>

ChessBoard::ChessBoard(const ChessBoard &other) {
  plane_ = other.plane_;
  move_counter_ = other.move_counter_;}

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

ChessBoard &ChessBoard::operator=(const ChessBoard &other) {
  if (&other == this)
    return *this;
  plane_ = other.plane_;
  move_counter_ = other.move_counter_;
  return *this;
}

Piece *&ChessBoard::operator[](unsigned int position) {
  return plane_[position];
}

Piece &ChessBoard::GetElement(unsigned int x, unsigned int y) {
  return *plane_[x * B_WIDTH + y];
}

double ChessBoard::EvaluatePosition() {

  double white_weight_of_move = 0.1;
  double black_weight_of_move = 0.1;

  /// if next round is white to move we boost wite evaluation
//  if (move_counter_ % 2 == 0)
//    black_weight_of_move += 0.07;
//  else
//    white_weight_of_move += 0.07;

  std::vector<Move> white_move_buffer;
  std::vector<Move> black_move_buffer;
  double eva = 0.0;

  for (int i = 0; i < 64; i++) {

    if (plane_[i]->Color()) {

      white_move_buffer.reserve(white_move_buffer.size() + 27);
      plane_[i]->GenMoves(plane_, i, white_move_buffer);

    } else {
      black_move_buffer.reserve(black_move_buffer.size() + 27);

      plane_[i]->GenMoves(plane_, i, black_move_buffer);
    }

    eva += plane_[i]->Value();
  }
  eva += white_move_buffer.size() * white_weight_of_move;
  eva -= black_move_buffer.size() * black_weight_of_move;

  return eva;
}

Piece &ChessBoard::GetElement(unsigned int position) {
  return *plane_[position];
}

void ChessBoard::DoMove(const Move &target) {
  plane_[target.to_] = plane_[target.from_]->Clone();
  plane_[target.to_]->SetMoved();

  //delete plane_[target.from_];
  plane_[target.from_] = new Piece();
  move_counter_++;
}


void ChessBoard::TransposeChessboard(ChessBoard &new_board,const Move &target) {

  new_board[target.to_] = new_board[target.from_]->Clone();
  new_board[target.to_]->SetMoved();

  //delete plane_[target.from_];
  new_board[target.from_] = new Piece();
  new_board.move_counter_++;

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

double ChessBoard::MinMax(ChessBoard &target, int depth, bool color) {

  double current_evaluation = EvaluatePosition();
  if (depth == 0)
    return current_evaluation;

  if (color) {                    // for white
    if (current_evaluation > 900) // if we just  mated fucker
      return current_evaluation;

    current_evaluation = -1000;

    std::vector<Move> move_buffer;
    GenAllPossibleMoves(P_WHITE, move_buffer);

    for (auto &i : move_buffer) {
      ChessBoard i_board(*this);
      TransposeChessboard(i_board,i);

      i.evaluation_ = target.MinMax(i_board, depth - 1, P_BLACK);
      if (i.evaluation_ > current_evaluation)
        current_evaluation = i.evaluation_;
    }

    return current_evaluation;

  } else {                         // for black
    if (current_evaluation < -900) // same but with black
      return current_evaluation;

    std::vector<Move> move_buffer;
    current_evaluation = 1000;

    GenAllPossibleMoves(P_WHITE, move_buffer);

    for (auto &i : move_buffer) {
      ChessBoard i_board(*this);
      TransposeChessboard(i_board,i);

      i.evaluation_ = target.MinMax(i_board, depth - 1, P_WHITE);

      if (i.evaluation_ < current_evaluation)
        current_evaluation = i.evaluation_;
    }
    return current_evaluation;
  }
}
