//
// Created by studio25 on 06.07.2021
//
#include "chess_board_gui.h"
#include "ppm_loader.h"
#include <SDL_ttf.h>

int ChessBoardGui::square_height_ = 64; // in pixels
int ChessBoardGui::square_width_ = 64;  // in pixels

int ChessBoardGui::height_ = 8; // in squares
int ChessBoardGui::width_ = 8;  // in squares

int Abs(int a) { return a < 0 ? -a : a; }

static std::array<SDL_Surface *, (int)PieceType::SIZE - 1> images;

static void LoadImagesToMemory() {
  std::string directory_path = "../gui/assets/";

  Uint32 r_mask = 0xff000000;
  Uint32 g_mask = 0x00ff0000;
  Uint32 b_mask = 0x0000ff00;
  Uint32 a_mask = 0x000000ff;

  for (int i = 0; i < (int)PieceType::SIZE - 1; i++) {
    images[i] =
        SDL_CreateRGBSurface(0, 60, 60, 32, r_mask, g_mask, b_mask, a_mask);

    if (images[i] == nullptr) {
      fprintf(stderr, "SDL_CreateRGBSurface() failed: %s", SDL_GetError());
      exit(1);
    }
  }

  LoadFromPpm(images[(int)PieceType::WHITE_PAWN],
              directory_path + "white_pawn.ppm");
  LoadFromPpm(images[(int)PieceType::WHITE_NIGHT],
              directory_path + "white_knight.ppm");
  LoadFromPpm(images[(int)PieceType::WHITE_BISHOP],
              directory_path + "white_bishop.ppm");
  LoadFromPpm(images[(int)PieceType::WHITE_ROOK],
              directory_path + "white_rook.ppm");
  LoadFromPpm(images[(int)PieceType::WHITE_QUEEN],
              directory_path + "white_queen.ppm");
  LoadFromPpm(images[(int)PieceType::WHITE_KING],
              directory_path + "white_king.ppm");
  LoadFromPpm(images[(int)PieceType::BLACK_PAWN],
              directory_path + "black_pawn.ppm");
  LoadFromPpm(images[(int)PieceType::BLACK_NIGHT],
              directory_path + "black_knight.ppm");
  LoadFromPpm(images[(int)PieceType::BLACK_BISHOP],
              directory_path + "black_bishop.ppm");
  LoadFromPpm(images[(int)PieceType::BLACK_ROOK],
              directory_path + "black_rook.ppm");
  LoadFromPpm(images[(int)PieceType::BLACK_QUEEN],
              directory_path + "black_queen.ppm");
  LoadFromPpm(images[(int)PieceType::BLACK_KING],
              directory_path + "black_king.ppm");
}

void ChessBoardGui::ClearHighlight() {
  Uint32 myEventType = SDL_RegisterEvents(1);

  if (myEventType != ((Uint32)-1)) {
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
    event.type = myEventType;
    event.user.code = (Sint32)(Events::CLEAR_HIGHLIGHT);
    SDL_PushEvent(&event);
  }
}

ChessBoardGui::ChessBoardGui() : local_board_() {
  window_ = nullptr; // all these will be initialized in thEvent Loop
                     // sdl requires that the initialization accrues in the same
                     // thread that usage
                     // (but that's just my observation)
  sans_ = nullptr;
  renderer_ = nullptr;

  // load piece's images from drive
  LoadImagesToMemory();
  LoadButtons();

  current_orientation_ = WHITE_UP;

  // for reasons unclear to me
  // sdl needs variables declared in thread they will be used
  window_thread_ = new std::thread(&ChessBoardGui::ThEventLoop, this);

  // that's why we wait here half a second
  // so that the variables can be filled in
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void ChessBoardGui::UpdateScreen() {
  Uint32 myEventType = SDL_RegisterEvents(1);

  if (myEventType != ((Uint32)-1)) {
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
    event.type = myEventType;
    event.user.code = (Sint32)(Events::UPDATE_SCREEN);
    SDL_PushEvent(&event);
  }
}

void ChessBoardGui::UpdateDisplay() {
  DrawSquares();
  DrawButtons();
  LabelSquares();
  DrawPieces();
  DrawEvaluation();
  SDL_RenderPresent(renderer_);
}

ChessBoardGui::~ChessBoardGui() {

  window_thread_->join();
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);

  // SDL_Quit();
}

void ChessBoardGui::ThEventLoop() {
  TTF_Init();

  sans_ = TTF_OpenFont("C:\\Users\\studio25\\Documents\\console_"
                       "chess\\gui\\assets\\STIXTwoMath-Regular.ttf",
                       16);

  TTF_SetFontStyle(sans_, TTF_STYLE_BOLD);

  if (!sans_) {
    std::cout << "the error: " << TTF_GetError();
  }

  window_ = SDL_CreateWindow("chess",          // window title
                             100,              // initial x position
                             100,              // initial y_ position
                             9 * 64,           // width, in pixels
                             8 * 64,           // height, in pixels
                             SDL_WINDOW_OPENGL // flags - see below
  );

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);

  DrawSquares();
  SDL_RenderPresent(renderer_);

  while (1 < 2) {

    SDL_WaitEvent(&event_);
    switch (event_.type) {
    case SDL_QUIT:
      active_ = false;
      return;
    case SDL_MOUSEBUTTONUP:
      int x, y;
      SDL_GetMouseState(&x, &y);
      CheckSquarePress(x, y);
      CheckButtonPress(x, y);
      UpdateDisplay();
      break;
    }
    switch ((Events)event_.user.code) {
    case Events::LOAD_BOARD:
      local_board_ = *(ChessBoard *)event_.user.data1;
      delete (ChessBoard *)event_.user.data1;
      break;
    case Events::HIGHLIGHT_SQUARE:
      highlighted_squares_.push_back({*(int *)event_.user.data1, {BLUE}});
      break;
    case Events::HIGHLIGHT_PIECE:
      highlighted_pieces_.push_back({*(int *)event_.user.data1, {BLUE}});
      break;
    case Events::UPDATE_SCREEN:
      UpdateDisplay();
      break;
    case Events::CLEAR_HIGHLIGHT:
      highlighted_squares_.clear();
      highlighted_pieces_.clear();
      break;
    }

    // std::this_thread::sleep_for(std::chrono::milliseconds(24));
  }
}

void ChessBoardGui::DrawSquares() {

  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 8; x++) {
      SDL_Rect square = {y * 64, x * 64, 64, 64};

      if (x % 2 == 0 xor y % 2 == 0)
        SDL_SetRenderDrawColor(renderer_, LIGHT_BLACK_COLOR);
      else
        SDL_SetRenderDrawColor(renderer_, LIGHT_WHITE_COLOR);

      SDL_RenderFillRect(renderer_, &square);
    }
  HighlightSquares();
}

void ChessBoardGui::LabelSquares() {

  int w = 4; // size of the label square
  int h = 4; // size of the label square

  // the coordinates point to the left bottom of the first board square

  SDL_Rect label_square = {0, 64, w, h};

  SDL_Color current_color;

  for (int y = 0; y < height_; y++) { // vertical ones are 1 to 8

    if (y % 2 == 0)

      current_color = {LIGHT_BLACK_COLOR};
    else
      current_color = {LIGHT_WHITE_COLOR};

    TTF_SizeText(sans_, GenRankLabel(y).c_str(), &w, &h);

    label_square = {(h / 4),
                    y * square_height_ + (square_height_ - h - (h / 6)), w, h};

    SDL_RenderCopy(
        renderer_,
        SDL_CreateTextureFromSurface(
            renderer_, TTF_RenderText_Solid(sans_, GenRankLabel(y).c_str(),
                                            current_color)),
        nullptr, &label_square);
  }

  for (int x = 0; x < width_; x++) { // vertical ones are a to h

    if (x % 2 == 0)
      current_color = {LIGHT_WHITE_COLOR};
    else
      current_color = {LIGHT_BLACK_COLOR};

    TTF_SizeText(sans_, GenFileLabel(x).c_str(), &w, &h);

    label_square = {
        x * square_width_ + square_width_ - w -
            (w / 4), // down, right corner of the botom rank
        (height_ - 1) * square_height_ + (square_height_ - h - (h / 6)), w, h};

    SDL_RenderCopy(
        renderer_,
        SDL_CreateTextureFromSurface(
            renderer_, TTF_RenderText_Solid(sans_, GenFileLabel(x).c_str(),
                                            current_color)),
        nullptr, &label_square);
  }
}

void ChessBoardGui::DrawPieces() {
  int flip = current_orientation_ == WHITE_UP ? 0 : 7;

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {

      DrawToRenderer({x * 64 + 2, y * 64 + 2, 60, 60},
                     local_board_.GetElement(Abs(y - flip), x).GetPieceType());
    }
  }
}

void ChessBoardGui::RotateBoard() {
  if (current_orientation_ == WHITE_UP)
    current_orientation_ = BLACK_UP;
  else
    current_orientation_ = WHITE_UP;
}

void ChessBoardGui::DrawToRenderer(SDL_Rect target_placement, PieceType pawn) {
  if (pawn == PieceType::NONE)
    return;

  // in CreateTextureFromSurface surface is not modified
  if (images[(int)pawn] == NULL) {
    fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
  }
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(renderer_, images[(int)pawn]);

  if (texture == NULL) {
    fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
  }

  SDL_RenderCopy(renderer_, texture, NULL, &target_placement);
  // SDL_DestroyTexture(texture);
}

std::string ChessBoardGui::GenRankLabel(int y) {
  if (current_orientation_ == WHITE_UP)
    return std::to_string(y + 1);
  else
    return std::to_string(height_ - y);
}

std::string ChessBoardGui::GenFileLabel(int x) {
  if (current_orientation_ == WHITE_UP)
    return std::string(1, (char)('a' + x));
  else
    return std::string(1, (char)('a' + width_ - 1 - x));
}

void ChessBoardGui::DrawEvaluation() {

  int w = 4; // size of the label square
  int h = 4; // size of the label square

  SDL_SetRenderDrawColor(renderer_, BLACK_COLOR);
  SDL_RenderFillRect(renderer_,
                     new SDL_Rect({width_ * square_width_, 20, 64, 20}));

  SDL_Rect evaluation_square = {width_ * square_width_ + w, 21, w, h};
  SDL_Color evaluation_color = {WHITE_COLOR};

  std::string evaluation_text = std::to_string(local_board_.EvaluatePosition());

  if (evaluation_text.size() > 5)
    evaluation_text = evaluation_text.substr(0, 5);

  TTF_SizeText(sans_, evaluation_text.c_str(), &evaluation_square.w,
               &evaluation_square.h);

  SDL_RenderCopy(
      renderer_,
      SDL_CreateTextureFromSurface(
          renderer_, TTF_RenderText_Solid(sans_, evaluation_text.c_str(),
                                          evaluation_color)),
      nullptr, &evaluation_square);
}

void ChessBoardGui::LoadButtons() {
  std::string directory_path = "../gui/assets/";

  buttons_[(int)Buttons::ROTATE_BOARD] =
      Button({width_ * square_width_, (height_ - 1) * square_height_,
              square_height_, square_width_});
  buttons_[(int)Buttons::ROTATE_BOARD].SetImage(directory_path +
                                                "board_rotation.ppm");

  buttons_[(int)Buttons::CLEAN_HIGHLIGHT] =
      Button({width_ * square_width_, (height_ - 2) * square_height_,
              square_height_, square_width_});

  buttons_[(int)Buttons::CLEAN_HIGHLIGHT].SetImage(directory_path +
                                                   "highlight_clean.ppm");
}

void ChessBoardGui::DrawButtons() {
  for (const auto &i : buttons_) {
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(renderer_, i.GetImage());

    if (texture == nullptr) {
      fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
    }

    SDL_RenderCopy(renderer_, texture, NULL, &i.GetPosition());
    SDL_DestroyTexture(texture);
  }
}

void ChessBoardGui::CheckButtonPress(int mouse_position_x,
                                     int mouse_position_y) {
  int pressed_button_id = 0;

  for (; pressed_button_id < (int)Buttons::SIZE; pressed_button_id++)
    if (buttons_[pressed_button_id].DetectPress(mouse_position_x,
                                                mouse_position_y))
      break;

  if (pressed_button_id == (int)Buttons::SIZE)
    return;

  switch ((Buttons)pressed_button_id) {
  case Buttons::ROTATE_BOARD:
    RotateBoard();
    break;
  case Buttons::CLEAN_HIGHLIGHT:
    ClearHighlight();
    break;
  }
}

void ChessBoardGui::CheckSquarePress(int x, int y) {

  x /= square_width_;
  y /= square_height_;

  if (x >= width_ or y >= height_)
    return;

  if (current_orientation_ == WHITE_UP)
    highlighted_squares_.emplace_back(y * width_ + x, ORANGE);
  else
    highlighted_squares_.emplace_back((height_ - y - 1) * width_ + x, ORANGE);
}

void ChessBoardGui::HighlightSquares() {
  SDL_Rect square;

  for (auto i : highlighted_squares_) {

    int h = i.first / width_;
    int w = i.first % width_;

    if (current_orientation_ == WHITE_UP)
      square = {w * square_width_, h * square_height_, square_width_,
                square_height_};
    else
      square = {w * square_width_, (height_ - h - 1) * square_height_,
                square_width_, square_height_};

    switch (i.second) {

    case ORANGE:

      if ((current_orientation_ == WHITE_UP) xor (w % 2 == 0 xor h % 2 == 0))
        SDL_SetRenderDrawColor(renderer_, LIGHT_ORANGE_COLOR);
      else
        SDL_SetRenderDrawColor(renderer_, ORANGE_COLOR);

      break;
    case BLUE:

      if ((current_orientation_ == WHITE_UP) xor (w % 2 == 0 xor h % 2 == 0))
        SDL_SetRenderDrawColor(renderer_, LIGHT_BLUE_COLOR);
      else
        SDL_SetRenderDrawColor(renderer_, BLUE_COLOR);

      break;

    }
    SDL_RenderFillRect(renderer_, &square);
  }
}

void ChessBoardGui::AnimateMove(Move target) {

  if (local_board_.GetElement(target.from_).IsEmpty())
    return;

  // length of one frame: 1/50s
  std::chrono::milliseconds frame_time(20);

  // whole time reserved for animation = 500ms
  unsigned number_of_key_frames = 500 / 20;

  // in squares
  unsigned from_y = target.from_ / 8, from_x = target.from_ % 8;
  unsigned to_y = target.to_ / 8, to_x = target.to_ % 8;

  // convert to pixels

  from_y *= square_height_;
  from_x *= square_width_;
  to_y *= square_height_;
  to_x *= square_width_;

  // generate key frames positions in equal spaces
  // they're sum must add up to number_of_key_frames

  // standard formula for distance between two points
  double travel_distance = sqrt(pow(from_x - to_x, 2) + pow(from_y - to_y, 2));
  // divide to get the distance in px between key frames
  travel_distance /= number_of_key_frames;

  std::vector<SDL_Rect> key_frames_positions;

  double dx = (double)(from_x - to_x) / number_of_key_frames;
  double dy = (double)(from_y - to_y) / number_of_key_frames;

  key_frames_positions.reserve(number_of_key_frames);

  for (int i = 0; i < number_of_key_frames; i++) {
    key_frames_positions.push_back({(int)(dx * i), (int)(dy * i), 60,
                                    60}); // 60, 60 <- piece image height, width
  }
}

/// pushes new load board event on to event stack,
/// to event.user.data field is assigned pointer to new board object
/// after updating the board this new board must be deleted!

void ChessBoardGui::LoadBoard(ChessBoard &board) {
  Uint32 myEventType = SDL_RegisterEvents(1);

  if (myEventType != ((Uint32)-1)) {
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
    event.type = myEventType;
    event.user.code = (Sint32)(Events::LOAD_BOARD);
    event.user.data1 = new ChessBoard(board);
    SDL_PushEvent(&event);
  }
}

/// pushes new HIGHLIGHT_SQUARE event onto event stack,
/// to event.user.data field is assigned pointer to int* object
/// after updating the board this object must be deleted!

void ChessBoardGui::HighlightSquare(int square_position) {
  Uint32 myEventType = SDL_RegisterEvents(1);
  if (myEventType != ((Uint32)-1)) {
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
    event.type = myEventType;
    event.user.code = (Sint32)(Events::HIGHLIGHT_SQUARE);
    event.user.data1 = new int(square_position);
    SDL_PushEvent(&event);
  }
}

/// pushes new HIGHLIGHT_SQUARE event onto event stack,
/// to event.user.data field is assigned pointer to int* object
/// after updating the board this object must be deleted!
void ChessBoardGui::HighlightPiece(int piece_position) {
  Uint32 myEventType = SDL_RegisterEvents(1);

  if (myEventType != ((Uint32)-1)) {
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
    event.type = myEventType;
    event.user.code = (Sint32)(Events::HIGHLIGHT_PIECE);
    event.user.data1 = new int(piece_position);
    SDL_PushEvent(&event);
  }
}

void ChessBoardGui::HighlightPieces() {

//  for(auto i:highlighted_pieces_)


}
