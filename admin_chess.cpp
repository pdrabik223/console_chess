//
// Created by pc on 23.04.2021.
//
#include <iostream>

#include "chess_board.h"
#include <Windows.h>
#include <vector>

int ChessToInt(std::string coord) {

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

enum Task {

  QUIT,
  MOVE,
  ADD_PIECE,
  ADD_ALL,
  DELETE_PIECE,
  DELL_ALL, // todo finish them
            //  i have 6 h of sleep to cath
  SHOW_MOVES,
  SHOW_POSSIBLE,
  NONE,
  HELP

};

struct full_command {

  full_command(Task t) : comm(t){};
  full_command(Task t, std::vector<int> data)
      : comm(t), data(std::move(data)){};

  Task comm;
  std::vector<int> data;
};

int main() {

  std::cout << "welcome to admin chess\n";

  ChessBoard game;

  std::string command;
  full_command buff = full_command(HELP);
  while (2 > 1) {
    game.ShowInConsole();
    std::cin >> command;

    if (buff.comm == QUIT)
      break;
  }
  return 0;
}

full_command Decode(std::string input) {

  if (input[0] == 'h' or input == "help")
    return {HELP};
  if (input[0] == 'q' or input == "quit") {
    return {QUIT};
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
    if (input.substr(0, 6) == "delete")
      input.erase(0, 6);
    // todo delete all
  }
  if ((input[0] == 's' and input[1] == ' ') or
      input.substr(0, 10) == "show moves") {
  }
  return {NONE};
}

void RunTask(ChessBoard &game, full_command input) {
  switch (input.comm) {

  case MOVE:
    game[input.data[1]] = game[input.data[0]];
    game[input.data[1]] = Piece();
    break;
  case ADD_PIECE:

    switch (input.data[1]) {
    case 0:
      game[input.data[2]] = Pawn(input.data[0]);
      break;
    case 1:
      game[input.data[2]] = Night(input.data[0]);
      break;
    case 2:
      game[input.data[2]] = Bishop(input.data[0]);
      break;
    case 3:
      game[input.data[2]] = Rook(input.data[0]);
      break;
    case 4:
      game[input.data[2]] = Queen(input.data[0]);
      break;
    case 5:
      game[input.data[2]] = King(input.data[0]);
      break;
    }

    break;
  case DELETE_PIECE:

    game[input.data[0]] = Piece();

    break;

  case SHOW_MOVES: {
    auto hc = GetStdHandle(STD_OUTPUT_HANDLE);
    int text_color = 0;
    int background_color = 0;
    std::array<Move, 27> move_buffer;

    if (game[input.data[0]].Color())
      text_color = 11;
    else
      text_color = 12;
    game[input.data[0]].GenMoves(game.plane_, input.data[0], move_buffer);

    SetConsoleTextAttribute(hc, text_color + background_color * 16);
    for (auto m : move_buffer)
      std::cout << (std::string)m;
  } break;
  case SHOW_POSSIBLE: {
    auto hc = GetStdHandle(STD_OUTPUT_HANDLE);
    int text_color = 0;
    int background_color = 0;
    std::array<Move, 27> move_buffer;
    for (int i = 0; i < 64; i++) {

      if (game[i].Color())
        text_color = 11;
      else
        text_color = 12;
      game[i].GenMoves(game.plane_, i, move_buffer);
      SetConsoleTextAttribute(hc, text_color + background_color * 16);
      for (auto m : move_buffer)
        std::cout << (std::string)m;
    }
  } break;
  case HELP:
    printf("help is coming\n"
           "add [Color][piece][position]    creates new [piece] in [position]\n"
           "add all returns the chessboard to original [position]\n"
           "del [position]  removes piece from [position]\n"
           "del all removes all pieces\n"
           "show moves [position]   shows moves that are possible to be made\n"
           "                        by the piece under [position]\n"
           "quit    quit the program\n"
           "move [position_from][position_to]   moves chosen by "
           "[position_from] piece"
           "                                    to selected by [position_to] "
           "square");
    break;
  }
}
