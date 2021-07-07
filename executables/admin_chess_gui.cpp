//
// Created by studio25 on 06.07.2021.
//

#include <iostream>

#include "gui/chess_board_gui.h"

int main(int argc, char *argv[]) {

  std::cout << "welcome to admin chess with gui!\n";

  ChessBoardGui ui;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  ChessBoard game;
  ui.UpdateDisplay(game);
  ui.UpdateScreen();
  while (1 < 2) {
    char h;
    // std::cin>>h;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ui.RotateBoard();
    if (ui.UpdateScreen())
      return 1;
  }

  return 0;
}
