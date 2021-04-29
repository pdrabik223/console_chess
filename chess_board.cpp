//
// Created by pc on 23.04.2021.
//
// todo if windows defined console output must change
//
#include "chess_board.h"
#include <Windows.h>

chess_board::chess_board(const chess_board &other) {

    plane = other.plane;
}

chess_board::chess_board() {

    plane[0] = new rook(BLACK);
    plane[1] = new night(BLACK);
    plane[2] = new bishop(BLACK);
    plane[3] = new queen(BLACK);
    plane[4] = new king(BLACK);
    plane[5] = new bishop(BLACK);
    plane[6] = new night(BLACK);
    plane[7] = new rook(BLACK);
    for(int i=8;i<16;++i) plane[i] = new pawn(BLACK);

    for(int i=16;i<48;++i) plane[i] = new piece();

    for(int i=48;i<56;++i) plane[i] = new pawn(WHITE);

    plane[56] = new rook(WHITE);
    plane[57] = new night(WHITE);
    plane[58] = new bishop(WHITE);
    plane[59] = new queen(WHITE);
    plane[60] = new king(WHITE);
    plane[61] = new bishop(WHITE);
    plane[62] = new night(WHITE);
    plane[63] = new rook(WHITE);

}


unsigned chess_board::size() {
    return 64;
}

chess_board &chess_board::operator=(const chess_board &other) {
    if (&other == this) return *this;
    plane = other.plane;
    return *this;
}

piece &chess_board::operator[](unsigned int position) {
    return *plane[position];
}

piece &chess_board::get_element(unsigned int x, unsigned int y) {
    return *plane[x * B_WIDTH + y];
}

double chess_board::evaluate() {

    double weight_of_move = 0.1;
    std::array<move, 27> move_buffer;

    double eva = 0.0;

    for (int i = 0; i < 64; i++) {

        plane[i]->gen_moves(plane, i, move_buffer);

        if (plane[i]->color()) {
            eva += (move_buffer.size() * weight_of_move);
        } else {
            eva -= (move_buffer.size() * weight_of_move);
        }

        eva += plane[i]->value();

    }
    return eva;


}

void chess_board::show_in_console() {
    auto hc = GetStdHandle(STD_OUTPUT_HANDLE);
    int text_color =0;
    int background_color =0;



    for (int x = 0; x < B_HEIGHT; ++x) {
        SetConsoleTextAttribute(hc, 13 + 0);
        printf("%d ",B_HEIGHT-x);
        for (int y = 0; y < B_WIDTH; ++y) {

            if(y % 2 == 0 xor x %2 == 0  ) background_color =0;
            else background_color = 8;

            if(get_element(x, y).color()) text_color = 11;
            else text_color = 12;

            SetConsoleTextAttribute(hc, text_color + background_color * 16);
            printf("%c ", (char) get_element(x, y));
        }
        if(x == 0 ) {
            if (evaluate()>0)text_color = 11;
            else text_color = 12;

            SetConsoleTextAttribute(hc, text_color + 0);
            printf("  eval: %lf", evaluate());
        }

        background_color = 15;
        SetConsoleTextAttribute(hc, text_color + background_color * 16);
        printf("\n");
    }
    SetConsoleTextAttribute(hc, 13 + 0);
    printf("  a b c d e f g h\n");


}



