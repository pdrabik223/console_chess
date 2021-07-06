//
// Created by studio25 on 06.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_
#define CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_

#include <SDL_main.h>
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "chess_board.h"
#include "move.h"

#include <vector>

class ChessBoardGui {
public:
  ChessBoardGui();

  ChessBoardGui &operator=(const ChessBoardGui &other);

  void UpdateScreen();

  void UpdateDisplay(ChessBoard &board);

  void AnimateMove(Move animate);

  void ClearHighlight();

  ~ChessBoardGui();

protected:
  ChessBoard local_board_;
  std::vector<std::pair<unsigned,SDL_Color>> highlighted_squares_;
  std::vector<std::pair<unsigned,SDL_Color>> highlighted_pieces_;

  SDL_Event event_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;

};

#endif // CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_
