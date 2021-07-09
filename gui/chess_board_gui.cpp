//
// Created by studio25 on 06.07.2021
//
#include "chess_board_gui.h"
#include "ppm_loader.h"

static std::array<SDL_Surface, SIZE - 1> images;


static void LoadImagesToMemory() {
  std::string directory_path = "../gui/assets/";

  LoadFromPpm(images[WHITE_PAWN],directory_path + "white_pawn.ppm");
  LoadFromPpm(images[WHITE_NIGHT],directory_path + "white_knight.ppm");
  LoadFromPpm(images[WHITE_BISHOP],directory_path + "white_bishop.ppm");
  LoadFromPpm(images[WHITE_ROOK],directory_path + "white_rook.ppm");
  LoadFromPpm(images[WHITE_QUEEN],directory_path + "white_queen.ppm");
  LoadFromPpm(images[WHITE_KING],directory_path + "white_king.ppm");
  LoadFromPpm(images[BLACK_PAWN],directory_path + "black_pawn.ppm");
  LoadFromPpm(images[BLACK_NIGHT],directory_path + "black_knight.ppm");
  LoadFromPpm(images[BLACK_BISHOP],directory_path + "black_bishop.ppm");
  LoadFromPpm(images[BLACK_ROOK],directory_path + "black_rook.ppm");
  LoadFromPpm(images[BLACK_QUEEN],directory_path + "black_queen.ppm");
  LoadFromPpm(images[BLACK_KING],directory_path + "black_king.ppm");
}



void ChessBoardGui::ClearHighlight() {
  highlighted_squares_.clear();
  highlighted_pieces_.clear();
}
ChessBoardGui::ChessBoardGui() : local_board_() {

  // load piece's images from drive
  LoadImagesToMemory();

  current_orientation_ = WHITE_UP;

  // for reasons unclear to me
  // sdl needs variables declared in thread they will be used
  window_thread_ = new std::thread(&ChessBoardGui::ThEventLoop, this);

  // that's why we wait here half a second
  // so that the variables can be filled in
  std::this_thread::sleep_for(std::chrono::milliseconds(500));

}
bool ChessBoardGui::UpdateScreen() {
  if (not active_)
    return false;
  SDL_RenderPresent(renderer_);
  return true;
}

void ChessBoardGui::UpdateDisplay(ChessBoard &board) {
  DrawSquares();
  local_board_ = board;
}

ChessBoardGui::~ChessBoardGui() {

  window_thread_->join();
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);

  // SDL_Quit();
}

void ChessBoardGui::ThEventLoop() {

  SDL_Event event;

  window_ = SDL_CreateWindow("chess",          // window title
                             100,                // initial x position
                             100,                // initial y_ position
                             9 * 64,            // width, in pixels
                             8 * 64,             // height, in pixels
                             SDL_WINDOW_OPENGL // flags - see below
  );

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);

  DrawSquares();
  DrawPieces();

  SDL_RenderPresent(renderer_);



  while (1 < 2) {
    SDL_WaitEvent(&event);

      switch (event.type) {
      case SDL_QUIT:
        active_ = false;
        return;
      case SDL_MOUSEMOTION:
        std::cout << "muse";
        break;
      case SDL_MOUSEBUTTONUP:

        RotateBoard();
        DrawSquares();
        DrawPieces();
        SDL_RenderPresent(renderer_);
        break;
      }

    std::cout<<"f";
    std::this_thread::sleep_for(std::chrono::milliseconds(24));
  }
}
void ChessBoardGui::DrawSquares() {

  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 8; x++) {
      SDL_Rect square = {y * 64, x * 64, 64, 64};

      if (current_orientation_ == WHITE_UP)
        if( x % 2 == 0 xor y % 2 == 0)
        SDL_SetRenderDrawColor(renderer_, LIGHT_WHITE_COLOR);
        else
        SDL_SetRenderDrawColor(renderer_, LIGHT_BLACK_COLOR);
      else
      if( x % 2 == 0 xor y % 2 == 0)
        SDL_SetRenderDrawColor(renderer_, LIGHT_BLACK_COLOR);
      else
        SDL_SetRenderDrawColor(renderer_, LIGHT_WHITE_COLOR);

      SDL_RenderFillRect(renderer_, &square);
    }

  for (auto &c : highlighted_squares_) {

    SDL_Rect square = {c.first / 8, c.first % 8, 64, 64};
    switch (c.second) {
    case WHITE:
      SDL_SetRenderDrawColor(renderer_, WHITE_COLOR);
      break;
    case BLACK:
      SDL_SetRenderDrawColor(renderer_, BLACK_COLOR);
      break;
    case BLUE:
      SDL_SetRenderDrawColor(renderer_, BLUE_COLOR);
      break;
    case RED:
      SDL_SetRenderDrawColor(renderer_, RED_COLOR);
      break;
    }
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 0);
    SDL_RenderFillRect(renderer_, &square);
  }
}
void ChessBoardGui::RotateBoard() {
if(current_orientation_ == WHITE_UP) current_orientation_ = BLACK_UP;
else current_orientation_ = WHITE_UP;
}

void DrawToRenderer(SDL_Renderer *renderer, SDL_Rect target_placement, PieceType pawn) {
  if(pawn == NONE) return;
  auto image = images[pawn];
  SDL_Rect image_contour = {0,0,64,64};
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, &image);
  SDL_RenderCopy(renderer, texture, &image_contour, &target_placement);
  SDL_DestroyTexture(texture);
}


void ChessBoardGui::DrawPieces() {

  for(int y = 0 ;y < 8;y++) {
    for (int x = 0; x < 8; x++){
      DrawToRenderer(renderer_,{x*64,y*64,64,64} ,local_board_.GetElement(x,y).GetPieceType());

    }
  }
}
