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

#include "arrow.h"
#include "button.h"
#include "chess_board.h"
#include "move.h"

/// there's no prettier way
/// unpack SDL_Color to it's r,b,g values
#define TO_UI8(x)                                                              \
  ChessBoardGui::colors_[(int)x].r, ChessBoardGui::colors_[(int)x].g,          \
      ChessBoardGui::colors_[(int)x].b, 0

/// there's no prettier way
/// create lighter version of a given color and
/// unpack SDL_Color to it's r,b,g values
#define TO_UI8_LIGHT(x)                                                        \
  Light(ChessBoardGui::colors_[(int)x]).r,                                     \
      Light(ChessBoardGui::colors_[(int)x]).g,                                 \
      Light(ChessBoardGui::colors_[(int)x]).b, 0

SDL_Color Light(SDL_Color target, unsigned char lightning_level = 60);

enum class GuiColor {
  WHITE,
  BLACK,
  ORANGE,
  BLUE,
  RED,
  PINK,
  GREEN,
  YELLOW,
  SIZE
};

enum Orientation { WHITE_UP = true, BLACK_UP = false };

enum class Buttons { ROTATE_BOARD, CLEAN_HIGHLIGHT, OPEN_MENU, SIZE };

enum class Events {
  UPDATE_SCREEN,
  LOAD_BOARD,
  HIGHLIGHT_SQUARE,
  HIGHLIGHT_PIECE,
  HIGHLIGHT_W_COLOR,
  /// display arrow
  HIGHLIGHT_MOVE,
  CLEAR_HIGHLIGHT
};

class ChessBoardGui {
public:
  ChessBoardGui();

  static void UpdateScreen();

  /// user accessible board modification
  static void LoadBoard(ChessBoard &board);

  static void HighlightSquare(int square_position);

  static void HighlightSquare(int square_position, GuiColor color);

  static void ClearHighlight();

  static void HighlightMove(Move target, unsigned size = 10, GuiColor color = GuiColor::RED);

  void HighlightPiece(int piece_position);

  ~ChessBoardGui();

private:
  ChessBoardGui &operator=(const ChessBoardGui &other);

  /// main loop
  void ThEventLoop();
  /// refresh screen function
  void UpdateDisplay();

  void RotateBoard();

  /// draw to renderer
  void AnimateMove(Move animate);

  void DrawSquares();

  void DrawPieces();

  void DrawLabels();

  void DrawEvaluation();

  void DrawButtons();

  void DrawArrows();

  void DrawHighlightedSquares();

  void DrawHighlightedPieces();

  void DrawPieceToRenderer(SDL_Rect target_placement, PieceType pawn);

  static int square_height_; // in pixels
  static int square_width_;  // in pixels

  static int height_; // in squares
  static int width_;  // in squares

  static std::array<SDL_Surface *, (int)PieceType::SIZE - 1> images_;
  static std::array<SDL_Color, (int)GuiColor::SIZE> colors_;

  static void LoadImagesToMemory();
  static void LoadColorsToMemory();
  void LoadButtonsToMemory();


  void CheckButtonPress(int mouse_position_x, int mouse_position_y);
  void CheckSquarePress(int mouse_position_x, int mouse_position_y);

  std::string GenRankLabel(int y);
  std::string GenFileLabel(int x);

protected:
  ChessBoard local_board_;

  std::vector<std::pair<int, GuiColor>> highlighted_squares_;
  std::vector<std::pair<int, GuiColor>> highlighted_pieces_;
  std::vector<Arrow> arrows_;

  std::array<Button, (size_t)Buttons::SIZE> buttons_;

  SDL_Window *window_;

  SDL_Renderer *renderer_;

  std::thread *window_thread_;

  TTF_Font *sans_;

  SDL_Event event_;

  Orientation current_orientation_;
};

#endif // CONSOLE_CHESS_GUI_CHESS_BOARD_GUI_H_
