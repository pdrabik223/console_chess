//
// Created by studio25 on 06.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_
#define CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_

#include <SDL_events.h>
#include <SDL_main.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <SDL_video.h>

#include <chrono>
#include <thread>
#include <vector>

#include "button.h"
#include "chess_board.h"
#include "move.h"

#define WHITE_COLOR 255, 255, 255, 0
#define LIGHT_WHITE_COLOR 200, 200, 200, 0

#define BLACK_COLOR 0, 0, 0, 0
#define LIGHT_BLACK_COLOR 74, 74, 74, 0

#define ORANGE_COLOR 216, 122, 21, 0
#define LIGHT_ORANGE_COLOR 216, 151, 86, 0

#define BLUE_COLOR 27, 91, 229, 0
#define LIGHT_BLUE_COLOR 126, 158, 229, 0

#define GREEN_COLOR 91, 226, 13, 0
#define LIGHT_GREEN_COLOR 147, 221, 104, 0

#define PINK_COLOR 224, 13, 129, 0
#define LIGHT_PINK_COLOR 219, 89, 161, 0

#define RED_COLOR 219, 17, 20, 0
#define LIGHT_RED_COLOR 219, 81, 83, 0

#define YELLOW_COLOR 216, 193, 19, 0
#define LIGHT_YELLOW_COLOR 216, 201, 82, 0

enum GuiColor { WHITE, BLACK, ORANGE, BLUE, RED, PINK, GREEN, YELLOW };

enum Orientation { WHITE_UP = true, BLACK_UP = false };

enum class Buttons { ROTATE_BOARD, CLEAN_HIGHLIGHT, OPEN_MENU, SIZE };

enum class Events {
  UPDATE_SCREEN,
  LOAD_BOARD,
  HIGHLIGHT_SQUARE,
  HIGHLIGHT_PIECE,
  HIGHLIGHT_MOVE,
  HIGHLIGHT_W_COLOR,
  CLEAR_HIGHLIGHT
};

class ChessBoardGui {
public:
  ChessBoardGui();

  static void UpdateScreen();

  static void LoadBoard(ChessBoard &board);

  static void HighlightMove(Move move_to_highlight);

  static void HighlightMove(Move move_to_highlight, GuiColor color);

  static void HighlightSquare(int square_position);

  static void ClearHighlight();

  void HighlightPiece(int piece_position);

  ~ChessBoardGui();

private:
  ChessBoardGui &operator=(const ChessBoardGui &other);

  void UpdateDisplay();

  void AnimateMove(Move animate);

  void DrawSquares();

  void DrawPieces();

  void ThEventLoop();

  void RotateBoard();

  void LabelSquares();

  void DrawEvaluation();

  void DrawButtons();

  bool active_ = true;

  static int square_height_; // in pixels
  static int square_width_;  // in pixels

  static int height_; // in squares
  static int width_;  // in squares

  void CheckButtonPress(int mouse_position_x, int mouse_position_y);
  void CheckSquarePress(int mouse_position_x, int mouse_position_y);

  void HighlightSquares();
  void HighlightPieces();

  void LoadButtons();

  void DrawToRenderer(SDL_Rect target_placement, PieceType pawn);

  std::string GenRankLabel(int y);
  std::string GenFileLabel(int x);

protected:
  ChessBoard local_board_;

  std::vector<std::pair<int, GuiColor>> highlighted_squares_;
  std::vector<std::pair<int, GuiColor>> highlighted_pieces_;
  int no_highlighted_moves_ = 0;

  std::array<Button, (size_t)Buttons::SIZE> buttons_;

  SDL_Window *window_;
  SDL_Renderer *renderer_;

  std::thread *window_thread_;

  TTF_Font *sans_;

  SDL_Event event_;

  Orientation current_orientation_;

  unsigned animation_time_ = 500; // in milliseconds
};

#endif // CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_
