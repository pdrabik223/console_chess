//
// Created by studio25 on 06.07.2021.
//

#include <iostream>

#include "GUI/chess_board_gui.h"

int main(int argc, char *argv[]) {

  std::cout << "welcome to admin chess with gui!\n";


  ChessBoard game;
  ChessBoardGui ui;
  ui.UpdateDisplay(game);
 char h;
  std::cin>>h;
  ui.UpdateScreen();


  return 0;
}
