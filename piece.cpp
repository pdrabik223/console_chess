//
// Created by pc on 23.04.2021.
//


#include "piece.h"

int c_cord(const unsigned &x, const unsigned &y) {
    return x * B_WIDTH + y;
}

bool add_move(std::array<piece *, 64> &board,
              std::array<move, 27> &possible_moves,
              piece *me,
              unsigned &last_move,
              const int &position,
              const int x, const int y) {

    if (board[c_cord(x, y)]->is_empty()) {
        possible_moves[last_move++] = {position, c_cord(x, y)};

    } else if (board[c_cord(x, y)]->color() != me->color()) {
        possible_moves[last_move++] = {position, c_cord(x, y)};
        return false;
    } else return false;
    return true;
}


/// i've got new rule
/// NEVER TEST ANYTHING
/// that's what lammers do
/// AND WE ARE PR06RAMM3R5
void pawn::gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves) {
    possible_moves.fill({0, 0});

    unsigned last_move = 0;
    if (color() == BLACK) {

        if (board[position + B_WIDTH]->is_empty()) possible_moves[last_move] = {position, position + B_WIDTH};
        last_move++;

        possible_moves[last_move] = {position, position + B_WIDTH - 1};
        last_move++;
        possible_moves[last_move] = {position, position + B_WIDTH + 1};
        last_move++;

        if (!moved()) {
            possible_moves[last_move] = {position, position + B_WIDTH * 2};
            last_move++;

        }
    } else {

        if (board[position - B_WIDTH]->is_empty()) possible_moves[last_move] = {position, position - B_WIDTH};
        last_move++;

        possible_moves[last_move] = {position, position - B_WIDTH - 1};
        last_move++;
        possible_moves[last_move] = {position, position - B_WIDTH + 1};
        last_move++;

        if (!moved()) {
            possible_moves[last_move] = {position, position - B_WIDTH * 2};
            last_move++;
        }

    }

}

void rook::gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves) {
    /// the x part of position
    const int px = position / B_WIDTH;
    /// the y part of position
    const int py = position % B_WIDTH;

    unsigned last_move = 0;
    possible_moves.fill({0, 0});


    for (int z = px + 1; z < 8; ++z) { // up
        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     z, py))
            break;
    }

    for (int z = px - 1; z >= 0; --z) { // down
        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     z, py))
            break;
    }

    for (int z = py + 1; z < 8; ++z) { // right
        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     px, z))
            break;
    }

    for (int z = py - 1; z >= 0; --z) { // left
        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     px, z))
            break;
    }
}

void bishop::gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves) {

    /// the x part of position
    const int px = position / B_WIDTH;
    /// the y part of position
    const int py = position % B_WIDTH;


    /// the temporary value
    int nx = px;

    int ny = py;


    unsigned last_move = 0;
    possible_moves.fill({0, 0});

    for (;;) { // right and down
        ++nx;
        ++ny;
        if (nx < B_WIDTH or ny < B_WIDTH) break;

        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     nx, ny))
            break;

    }
    for (;;) { // right and up
        --nx;
        ++ny;
        if (nx >= 0 or ny < B_WIDTH) break;

        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     nx, ny))
            break;

    }
    for (;;) { // left and up
        --nx;
        --ny;
        if (nx >= 0 or ny >= 0) break;

        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     nx, ny))
            break;

    }
    for (;;) { // left and down
        ++nx;
        --ny;
        if (nx < B_WIDTH or ny >= 0) break;

        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     nx, ny))
            break;

    }
}

void queen::gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves) {

    /// the x part of position
    const int px = position / B_WIDTH;
    /// the y part of position
    const int py = position % B_WIDTH;

    unsigned last_move = 0;
    possible_moves.fill({0, 0});


    for (int z = px + 1; z < 8; ++z) { // up
        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     z, py))
            break;
    }

    for (int z = px - 1; z >= 0; --z) { // down
        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     z, py))
            break;
    }

    for (int z = py + 1; z < 8; ++z) { // right
        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     px, z))
            break;
    }

    for (int z = py - 1; z >= 0; --z) { // left
        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     px, z))
            break;
    }


    /// the temporary value
    int nx = px;

    int ny = py;

    for (;;) { // right and down
        ++nx;
        ++ny;
        if (nx < B_WIDTH or ny < B_WIDTH) break;

        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     nx, ny))
            break;

    }
    for (;;) { // right and up
        --nx;
        ++ny;
        if (nx >= 0 or ny < B_WIDTH) break;

        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     nx, ny))
            break;

    }
    for (;;) { // left and up
        --nx;
        --ny;
        if (nx >= 0 or ny >= 0) break;

        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     nx, ny))
            break;

    }
    for (;;) { // left and down
        ++nx;
        --ny;
        if (nx < B_WIDTH or ny >= 0) break;

        if (add_move(board,
                     possible_moves,
                     this,
                     last_move,
                     position,
                     nx, ny))
            break;

    }

}

void king::gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves) {

    /// the x part of position
    const int px = position / B_WIDTH;
    /// the y part of position
    const int py = position % B_WIDTH;

    int nx = px;
    int ny = py;

    unsigned last_move = 0;
    possible_moves.fill({0, 0});

    nx = px - 1;
    ny = py - 1;
    if (nx >= 0 and ny >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px - 1;
    ny = py;
    if (nx >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px - 1;
    ny = py + 1;
    if (nx >= 0 and ny < B_WIDTH)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};


    nx = px;
    ny = py - 1;
    if (ny >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px;
    ny = py + 1;
    if (ny < B_WIDTH)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};


    nx = px + 1;
    ny = py - 1;
    if (nx < B_WIDTH and ny >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px + 1;
    ny = py;
    if (nx < B_WIDTH)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px + 1;
    ny = py + 1;
    if (nx < B_WIDTH and ny < B_WIDTH)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};


}

void night::gen_moves(std::array<piece *, 64> &board, const int position, std::array<move, 27> &possible_moves) {


    /// the x part of position
    const int px = position / B_WIDTH;
    /// the y part of position
    const int py = position % B_WIDTH;

    int nx = px;
    int ny = py;

    unsigned last_move = 0;
    possible_moves.fill({0, 0});

    nx = px - 2; // px -2
    ny = py - 1;
    if (nx >= 0 and ny >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px - 2;
    ny = py + 1;
    if (nx >= 0 and ny < B_WIDTH)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};


    nx = px + 1;
    ny = py - 2;
    if (nx < B_WIDTH and ny >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px - 1;
    ny = py - 2;
    if (nx >= 0 and ny >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};


    nx = px + 1;
    ny = py - 2;
    if (nx < B_WIDTH and ny >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};


    nx = px - 1;
    ny = py + 2;
    if (nx >= 0 and ny < B_WIDTH)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px + 1;
    ny = py + 2;
    if (nx < B_WIDTH and ny < B_WIDTH)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px + 2; // px -2
    ny = py - 1;
    if (nx < B_WIDTH and ny >= 0)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};

    nx = px + 2;
    ny = py + 1;
    if (nx < B_WIDTH and ny < B_WIDTH)
        if (board[c_cord(nx, ny)]->is_empty() or board[c_cord(nx, ny)]->color() != color())
            possible_moves[last_move++] = {position, c_cord(nx, ny)};


}
