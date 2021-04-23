//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS_PIECE_H
#define CONSOLE_CHESS_PIECE_H


#include "chess_board.h"
#include "move.h"

#define BLACK 0
#define WHITE 1


class piece {
public:

    piece() : info(BLACK) {}

    piece(const piece &other) = default;

    virtual explicit operator char() const { return 'e'; }

    bool color() const  { return info & 1; }

    bool moved() const  { return info & 2; }

    virtual void gen_moves(const chess_board* chess_board, const int position, std::array<mov,27>& possible_moves){};

protected:
    /// to save space and copy time, and we will do a lot of copying
    /// we use flag system
    /// least significant bit: colour
    /// black 0 white 1
    /// next if moved
    /// 1 moved 0 if not
    unsigned char info;

};


class king : public piece {
    king() { info = BLACK; }

    explicit king(char color) { info = color; }

    king(const king &other) = default;


    explicit operator char() const override { return 'k'; }
    virtual void gen_moves(const chess_board* chess_board, const int position, std::array<move,27>& possible_moves);

};

class queen : public piece {
    queen() { info = BLACK; }

    explicit queen(char color) { info = color; }

    queen(const queen &other) = default;


    explicit operator char() const override { return 'q'; }
    virtual void gen_moves(const chess_board* chess_board, const int position, std::array<move,27>& possible_moves);

};

class night : public piece {
    night() { info = BLACK; }

    explicit night(char color) { info = color; }

    night(const night &other) = default;


    explicit operator char() const override { return 'n'; }
    virtual void gen_moves(const chess_board* chess_board, const int position, std::array<move,27>& possible_moves);


};

class pawn : public piece {
    pawn() { info = BLACK; }

    explicit pawn(char color) { info = color; }

    pawn(const pawn &other) = default;


    explicit operator char() const override { return 'p'; }
    virtual void gen_moves(const chess_board* chess_board, const int position, std::array<move,27>& possible_moves);
};


class bishop : public piece {
    bishop() { info = BLACK; }

    explicit bishop(char color) { info = color; }

    bishop(const bishop &other) = default;


    explicit operator char() const override { return 'b'; }
    virtual void gen_moves(const chess_board* chess_board, const int position, std::array<move,27>& possible_moves);

};

class rook : public piece {
    rook() { info = BLACK; }

    explicit rook(char color) { info = color; }


    explicit operator char() const override { return 'r'; }
    virtual void gen_moves(const chess_board* chess_board, const int position, std::array<move,27>& possible_moves);



};

#endif //CONSOLE_CHESS_PIECE_H
