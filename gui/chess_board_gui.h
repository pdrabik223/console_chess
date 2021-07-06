//
// Created by studio25 on 06.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_
#define CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_

#include <SDL_events.h>
#include <SDL_main.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include "chess_board.h"
#include "move.h"

#include <vector>
#include <chrono>
#include <thread>

#define WHITE_COLOR 255,255,255,0
#define LIGHT_WHITE_COLOR 200,200,200,0
#define BLACK_COLOR 0,0,0,0
#define LIGHT_BLACK_COLOR 74,74,74,0
#define BLUE_COLOR 0,0,255,0
#define RED_COLOR 255,0,0,0
enum GuiColor{
  WHITE,
  BLACK,
  BLUE,
  RED

};
enum Orientation{
  WHITE_UP,
  BLACK_UP


};

class ChessBoardGui {
public:
  ChessBoardGui();

  ChessBoardGui &operator=(const ChessBoardGui &other);

  void UpdateScreen();

  void UpdateDisplay(ChessBoard &board);

  void AnimateMove(Move animate);

  void DrawSquares();

  void ClearHighlight();

  void ThEventLoop();

  ~ChessBoardGui();

protected:
  ChessBoard local_board_;
  std::vector<std::pair<int, GuiColor>> highlighted_squares_;
  std::vector<std::pair<int, GuiColor>> highlighted_pieces_;

  SDL_Event event_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;

  std::thread* window_thread_;

  Orientation  current_orientation_;
};

#endif // CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_
