//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS_PAWNS_PIECE_H_
#define CONSOLE_CHESS_PAWNS_PIECE_H_

#include "move.h"
#include <array>
#include <iostream>
#include <vector>

#define P_BLACK false
#define P_WHITE true

#define B_HEIGHT 8
#define B_WIDTH 8

class Piece {

public:
  Piece() : info_(P_BLACK) {}

  Piece(const Piece &other) = default;

  virtual explicit operator char() const { return ' '; }

  virtual bool IsEmpty() { return true; }

  /// \return true if white
  /// \return false if black
  virtual bool Color() const { return info_ bitand 1; }

  virtual bool Moved() const { return info_ bitand 2; }

  virtual double Value() const { return 0.0; }
  ///
  /// \param board current state of chess board
  /// \param position of this pawn
  /// \param possible_moves output of this function

  virtual void GenMoves(std::array<Piece *, 64> &board,
                        unsigned int position,
                        std::vector<Move> &possible_moves) {

  };

  virtual Piece *Clone(){return new Piece(* this);};


protected:
  virtual void GenMovesForBlack(std::array<Piece *, 64> &board,
                                const unsigned int position,
                                std::vector<Move> &possible_moves) {

  };

  virtual void GenMovesForWhite(std::array<Piece *, 64> &board,
                                const unsigned int position,
                                std::vector<Move> &possible_moves) {

  };

  /// to save space and copy time, and we will do a lot of copying
  /// we use flag system
  /// least significant bit: colour
  /// black 0 white 1
  /// next if Moved
  /// 1 Moved 0 if not
  unsigned char info_;
};

bool AddMove(std::array<Piece *, 64> &board, std::vector<Move> &possible_moves,
             bool color, const unsigned position, unsigned int target);


unsigned CCord(const unsigned &x, const unsigned &y);
#endif // CONSOLE_CHESS_PAWNS_PIECE_H_
