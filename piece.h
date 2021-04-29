//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS_PIECE_H
#define CONSOLE_CHESS_PIECE_H

#include "move.h"
#include <array>
#include <iostream>

#define BLACK 0
#define WHITE 1

#define B_HEIGHT 8
#define B_WIDTH 8

class piece {

public:

    piece() : info(BLACK) {}

    piece(const piece &other) = default;

    virtual explicit operator char() const { return ' '; }



    static bool is_empty() { return true; }

    /// \return true if white
    /// \return false if black
    bool color() const { return info bitand 1; }

    bool moved() const { return info bitand 2; }

    virtual double value() const { return 0.0; }

    virtual void gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves) {
        possible_moves.fill({0, 0});
    };
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
public:
    king() { info = BLACK; }

    explicit king(char color) { info = color; }

    king(const king &other) = default;

    double value() const { if (color()) return 999; else return -999; }

    static bool empty() { return false; }

    explicit operator char() const override { return 'k'; }

    void gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves);

};

class queen : public piece {
public:

    queen() { info = BLACK; }

    explicit queen(char color) { info = color; }

    queen(const queen &other) = default;


    double value() const { if (color()) return 9; else return -9; }
    static bool empty() { return false; }


    explicit operator char() const override { return 'q'; }

    void gen_moves(std::array<piece *, 64> &board, int position, std::array<move, 27> &possible_moves);

};

class night : public piece {
public:
    night() { info = BLACK; }

    explicit night(char color) { info = color; }

    double value() const { if (color()) return 3; else return -3; }

    night(const night &other) = default;

    static bool empty() { return false; }

    explicit operator char() const override { return 'n'; }

    void gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves);


};

class pawn : public piece {
public:
    pawn() { info = BLACK; }

    explicit pawn(char color) { info = color; }

    pawn(const pawn &other) = default;

    double value() const { if (color()) return 1; else return -1; }

    static bool empty() { return false; }

    explicit operator char() const override { return 'p'; }

    void gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves);
};


class bishop : public piece {
public:
    bishop() { info = BLACK; }

    explicit bishop(char color) { info = color; }

    bishop(const bishop &other) = default;
    double value() const override { if (color()) return 3.5; else return -3.5; }

    bool empty() { return false; }

    explicit operator char() const override { return 'b'; }

    void gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves);

};

class rook : public piece {
public:
    rook() { info = BLACK; }

    explicit rook(char color) { info = color; }

    double value() const override { if (color()) return 5; else return -5; }
    static bool empty() { return false; }

    explicit operator char() const override { return 'r'; }

    void gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves);


};

#endif //CONSOLE_CHESS_PIECE_H
