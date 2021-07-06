//
// Created by studio25 on 06.07.2021
//
#include "chess_board_gui.h"
void ChessBoardGui::ClearHighlight() {
  highlighted_squares_.clear();
  highlighted_pieces_.clear();
}
ChessBoardGui::ChessBoardGui() : local_board_() {

  window = SDL_CreateWindow("lele",           // window title
                            100,              // initial x position
                            100,              // initial y_ position
                            9 * 64,           // width, in pixels
                            8 * 64,           // height, in pixels
                            SDL_WINDOW_OPENGL // flags - see below
  );

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
}
void ChessBoardGui::UpdateScreen() {
  SDL_RenderPresent(renderer);
}
void ChessBoardGui::UpdateDisplay(ChessBoard &board) { local_board_ = board; }

ChessBoardGui::~ChessBoardGui() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
