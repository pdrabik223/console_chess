//
// Created by pc on 23.04.2021.
//
#include <iostream>

#include <vector>
#include "chess_board.h"
#include <Windows.h>
#include "move.h"
int chess_to_int(std::string coord) {

    switch (coord[0]) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
            return (B_HEIGHT - coord[1] + 1) * B_HEIGHT + coord[3] - 1;
        default:
            return -1;
    }

}

enum task {

    quit,
    move,
    add_piece,
    add_all,
    delete_piece,
    dell_all,//todo finish them
            // i have 6 h of sleep to cath
    show_moves,
    show_possible,
    help

};

struct full_command {
    full_command(task t) : comm(t) {};
    full_command(task t, std::vector<int> data) : comm(t), data(std::move(data)) {};

    task comm;
    std::vector<int> data;

};


int main() {


    std::cout << "welcome to admin chess\n";

    chess_board game;

    std::string command;
    full_command buff = full_command(help);
    while (2 > 1) {
        game.show_in_console();
        std::cin >> command;

        if (buff.comm == quit) break;

    }
    return 0;
}

full_command decode(std::string input) {

    if (input[0] == 'h' or input == "help") return {help};
    if (input[0] == 'q' or input == "quit") {
        return {quit};
    }
    if (input[0] == 'a' or input.substr(0, 3) == "add") {
        // for simplification
        // king = 5
        // queen = 4
        // rook = 3
        // bishop = 2
        // night = 1
        // pawn = 0

// todo add all


    }
    if (input[0] == 'd' or input.substr(0, 3) == "del") {
        if (input.substr(0, 6) == "delete") input.erase(0, 6);
// todo delete all

    }
    if ((input[0] == 's' and input[1] == ' ') or input.substr(0, 10) == "show moves") {


    }


}

void run_task(chess_board &game, full_command input) {
    switch (input.comm) {

        case move:
            game[input.data[1]] = game[input.data[0]];
            game[input.data[1]] = piece();
            break;
        case add_piece:

            switch (input.data[1]) {
                case 0:
                    game[input.data[2]] = pawn(input.data[0]);
                    break;
                case 1:
                    game[input.data[2]] = night(input.data[0]);
                    break;
                case 2:
                    game[input.data[2]] = bishop(input.data[0]);
                    break;
                case 3:
                    game[input.data[2]] = rook(input.data[0]);
                    break;
                case 4:
                    game[input.data[2]] = queen(input.data[0]);
                    break;
                case 5:
                    game[input.data[2]] = king(input.data[0]);
                    break;
            }

            break;
        case delete_piece:

            game[input.data[0]] = piece();

            break;

        case show_moves: {
            auto hc = GetStdHandle(STD_OUTPUT_HANDLE);
            int text_color = 0;
            int background_color = 0;
            std::array<move, 27> move_buffer;

            if (game[input.data[0]].color()) text_color = 11;
            else text_color = 12;
            game[input.data[0]].gen_moves(game, input.data[0], move_buffer);

            SetConsoleTextAttribute(hc, text_color + background_color * 16);
            for (auto m:move_buffer) std::cout << (std::string) m;
        }break;
        case show_possible: {
            auto hc = GetStdHandle(STD_OUTPUT_HANDLE);
            int text_color = 0;
            int background_color = 0;
            std::array<move, 27> move_buffer;
            for (int i = 0; i < 64; i++) {

                if (game[i].color()) text_color = 11;
                else text_color = 12;
                game[i].gen_moves(game, i, move_buffer);
                SetConsoleTextAttribute(hc, text_color + background_color * 16);
                for (auto m:move_buffer) std::cout << (std::string) m;


            }
        }break;
        case help:
            printf("help is coming\n"
                   "add [color][piece][position]    creates new [piece] in [position]\n"
                   "add all returns the chessboard to original [position]\n"
                   "del [position]  removes piece from [position]\n"
                   "del all removes all pieces\n"
                   "show moves [position]   shows moves that are possible to be made\n"
                   "                        by the piece under [position]\n"
                   "quit    quit the program\n"
                   "move [position_from][position_to]   moves chosen by [position_from] piece"
                   "                                    to selected by [position_to] square");
            break;
    }


}
