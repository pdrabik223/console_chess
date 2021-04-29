//
// Created by pc on 23.04.2021.
//
#include <iostream>
#include <utility>
#include <vector>
#include "chess_board.h"

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
    delete_piece,
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
// todo add all


    }
    if (input[0] == 'd' or input.substr(0, 3) == "del") {
        if (input.substr(0, 6) == "delete") input.erase(0, 6);
// todo delete all

    }
    if ((input[0] == 's' and input[1] == ' ') or input.substr(0, 10) == "show moves") {


    }

    if ((input[0] == 's' and input[1] == 'p') or input.substr(0, 10) == "show possible") {


    }


}