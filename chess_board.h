//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS_CHESS_BOARD_H
#define CONSOLE_CHESS_CHESS_BOARD_H

#include "pawns/piece.h"
#include <array>

#define B_HEIGHT 8
#define B_WIDTH 8

#define BLACK 0
#define WHITE 1
/// \brief
/// by default white start on bottom
class chess_board {
public:
    chess_board();
    chess_board(const chess_board& other);
    chess_board& operator=(const chess_board& other);

    /// returns size of the chess board
    static unsigned size();

    Piece & get_element(unsigned x,unsigned y);
    Piece & operator[](unsigned position);

    double evaluate();
    void show_in_console();

    std::array<Piece *,64> plane;
protected :


private:
    bool white_king_in_check;
    bool black_king_in_check;


};


#endif //CONSOLE_CHESS_CHESS_BOARD_H
