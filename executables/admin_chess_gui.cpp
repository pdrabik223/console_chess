//
// Created by studio25 on 06.07.2021.
//

#include <iostream>

#include "GUI/chess_board_gui.h"

int main(int argc, char *argv[]) {

  std::cout << "welcome to admin chess with GUI!\n";

  //AdminGui game;
  // std::this_thread::sleep_for(std::chrono::seconds(3));

  ChessBoard game;
  ChessBoardGui ui;
  ui.UpdateDisplay(game);
  ui.UpdateScreen();


  return 0;
}
