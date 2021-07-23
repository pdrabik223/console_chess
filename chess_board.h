//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS__CHESS_BOARD_H_
#define CONSOLE_CHESS__CHESS_BOARD_H_

#include "pawns/bishop.h"
#include "pawns/king.h"
#include "pawns/night.h"
#include "pawns/pawn.h"
#include "pawns/queen.h"
#include "pawns/rook.h"
#include <array>
#include <map>
#include <vector>

#define B_HEIGHT 8
#define B_WIDTH 8

#define P_BLACK false
#define P_WHITE true

/// \brief
/// by default white start on bottom
class ChessBoard {
public:
  ChessBoard();
  ChessBoard(const ChessBoard &other);
  ChessBoard &operator=(const ChessBoard &other);

  Piece &GetElement(unsigned h, unsigned w);
  Piece &GetElement(unsigned position);
  Piece *&operator[](unsigned position);

  void DoMove(const Move &target);
  Move DoRandomMove(bool color);


  void TransposeChessboard(ChessBoard &output_board, const Move &target);

  double EvaluatePosition();
  void EvaluateMove(Move &target);

  double MinMax(ChessBoard &target, int depth, bool color);

  double AlfaBetaMinMax(ChessBoard &target, int depth, double alfa, double beta,
                        bool color);

  double AlfaBetaMinMaxTranspositionTable(ChessBoard &target, int depth, double alfa, double beta,
                                          bool color,
      std::map<size_t, double> &transposition_table);

  unsigned int Hash();

  void GenAllPossibleMoves(bool color, std::vector<Move> &possible_moves);

  std::array<Piece *, 64> plane_;

  /// current move counter
  /// white player moves when move_counter % 2 == 0
  unsigned move_counter_ = 0;

  void LoadPosition(const std::string &path);

private:
  bool white_king_in_check_;
  bool black_king_in_check_;

};

#endif // CONSOLE_CHESS__CHESS_BOARD_H_
