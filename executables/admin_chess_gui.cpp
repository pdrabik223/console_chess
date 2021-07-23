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

  game.DoMove({10,18});


  while(true){

    Move temp = game.DoRandomMove(true);
    ui.ClearHighlight();
    ui.HighlightSquare(temp.from_);
    ui.HighlightSquare(temp.to_);

    ui.LoadBoard(game);
    ui.UpdateScreen();
    std::this_thread::sleep_for(std::chrono::seconds(1));


    temp = game.DoRandomMove(false);
    ui.ClearHighlight();
    ui.HighlightSquare(temp.from_);
    ui.HighlightSquare(temp.to_);

    ui.LoadBoard(game);
    ui.UpdateScreen();
    std::this_thread::sleep_for(std::chrono::seconds(1));

  }

  return 0;
}
