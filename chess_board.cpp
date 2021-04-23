//
// Created by pc on 23.04.2021.
//

#include "chess_board.h"

chess_board::chess_board(const chess_board &other) {

    plane = other.plane;
}

chess_board::chess_board() {
;
}


unsigned chess_board::size() {
    return 64;
}

chess_board &chess_board::operator=(const chess_board &other) {
if(&other == this) return *this;
    plane = other.plane;
    return *this;
}

piece &chess_board::operator[](unsigned int position) {
    return plane[position];
}

piece &chess_board::get_element(unsigned int x, unsigned int y) {
    return plane[x/B_WIDTH+y];
}

