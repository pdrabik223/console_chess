//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS_CHESS_BOARD_H
#define CONSOLE_CHESS_CHESS_BOARD_H


#include <array>
#include "piece.h"

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


    piece& get_element(unsigned x,unsigned y);
    piece& operator[](unsigned position);

    double evaluate();
    void show_in_console();

protected :
    std::array<piece*,64> plane;

private:
    bool white_king_in_check;
    bool black_king_in_check;


};


#endif //CONSOLE_CHESS_CHESS_BOARD_H
