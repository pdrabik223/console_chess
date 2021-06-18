//
// Created by pc on 23.04.2021.
//
#include <iostream>

#include "chess_board.h"
#include <vector>
#include <windows.h>


int main() {

  std::cout << "welcome to admin chess\n";

  ChessBoard game;

  std::string command;
  full_command buff = full_command(HELP);
  while (2 > 1) {
    game.ShowInConsole();
    std::cin >> command;
    buff = Decode(command);
    if (buff.comm == QUIT)
      break;
    if (buff.comm == NONE)
      continue;
    RunTask(game, buff);
  }
  return 0;
}

