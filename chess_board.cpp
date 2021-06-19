//
// Created by pc on 23.04.2021.
//
// todo if windows defined console output must change
//
#include "chess_board.h"
#include <Windows.h>

ChessBoard::ChessBoard(const ChessBoard &other) { plane_ = other.plane_;
}

ChessBoard::ChessBoard() {

  plane_[0] = new Rook(P_BLACK);
  plane_[1] = new Night(P_BLACK);
  plane_[2] = new Bishop(P_BLACK);
  plane_[3] = new Queen(P_BLACK);
  plane_[4] = new King(P_BLACK);
  plane_[5] = new Bishop(P_BLACK);
  plane_[6] = new Night(P_BLACK);
  plane_[7] = new Rook(P_BLACK);
    for(int i=8;i<16;++i)
      plane_[i] = new Pawn(P_BLACK);

    for(int i=16;i<48;++i)
      plane_[i] = new Piece();

    for(int i=48;i<56;++i)
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


unsigned ChessBoard::Size() {
    return 64;
}

ChessBoard &ChessBoard::operator=(const ChessBoard &other) {
    if (&other == this) return *this;
    plane_ = other.plane_;
    return *this;
}

Piece *&ChessBoard::operator[](unsigned int position) {
    return plane_[position];
}

Piece &ChessBoard::GetElement(unsigned int x, unsigned int y) {
    return *plane_[x * B_WIDTH + y];
}

double ChessBoard::Evaluate() {

    double weight_of_move = 0.1;
    std::array<Move, 27> move_buffer;

    double eva = 0.0;

    for (int i = 0; i < 64; i++) {

      plane_[i]->GenMoves(plane_, i, move_buffer);

        if (plane_[i]->Color()) {
            eva += (move_buffer.size() * weight_of_move);
        } else {
            eva -= (move_buffer.size() * weight_of_move);
        }

        eva += plane_[i]->Value();

    }
    return eva;


}

void ChessBoard::ShowInConsole() {
    auto hc = GetStdHandle(STD_OUTPUT_HANDLE);
    int text_color =0;
    int background_color =0;



    for (int x = 0; x < B_HEIGHT; ++x) {
        SetConsoleTextAttribute(hc, 13 + 0);
        printf("%d ",B_HEIGHT-x);
        for (int y = 0; y < B_WIDTH; ++y) {

            if(y % 2 == 0 xor x %2 == 0  ) background_color =0;
            else background_color = 8;

            if(GetElement(x, y).Color()) text_color = 11;
            else text_color = 12;

            SetConsoleTextAttribute(hc, text_color + background_color * 16);
            printf("%c ", (char)GetElement(x, y));
        }
        if(x == 0 ) {
            if (Evaluate()>0)text_color = 11;
            else text_color = 12;

            SetConsoleTextAttribute(hc, text_color + 0);
            printf("  eval: %lf", Evaluate());
        }

        background_color = 15;
        SetConsoleTextAttribute(hc, text_color + background_color * 16);
        printf("\n");
    }
    SetConsoleTextAttribute(hc, 13 + 0);
    printf("  a b c d e f g h\n");
  SetConsoleTextAttribute(hc, 16 + 0);



}

Piece &ChessBoard::GetElement(unsigned int position) {
  return *plane_[position];
}
