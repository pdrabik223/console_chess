//
// Created by studio25 on 06.07.2021.
//

#include <gui/admin_gui.h>
#include <iostream>

#include "gui/chess_board_gui.h"

int main(int argc, char *argv[]) {

  std::cout << "welcome to admin chess with gui!\n";

//  ChessBoardGui ui;
//
//  std::this_thread::sleep_for(std::chrono::seconds(1));
//
//  ChessBoard game;
//
//
//  while(true){
//
//    Move temp = game.DoRandomMove(true);
//   // ui.ClearHighlight();
//    ui.HighlightCircle(temp.to_);
//    ui.LoadBoard(game);
//    ui.UpdateScreen();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//
//
//    temp = game.DoRandomMove(false);
//  //  ui.ClearHighlight();
//    ui.HighlightCircle(temp.to_);
//
//
//    ui.LoadBoard(game);
//    ui.UpdateScreen();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//
//  }

  AdminGui game;

  return 0;
}
