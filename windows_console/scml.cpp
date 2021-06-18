//
// Created by studio25 on 26.05.2021.
//

#include "scml.h"
#include <cassert>
#include <string>


Scml::Scml() {

  hc_ = GetStdHandle(STD_OUTPUT_HANDLE);
  _setmode(_fileno(stdout), _O_U16TEXT);

  for (int y = 0; y < h_; y++) {

    for (int x = 0; x < w_; x++) {
      col::Color background;
      col::Color text = LIGHT_AQUA;
      if (y % 2 == 0 xor x % 2 == 0)
        background = col::BLACK;
      else
        background = col::GRAY;

      buffer_[y][x] = {' ', text, background};
    }
  }

  current_evaluation_ = 0;

  /// here when I wrote    buffer.emplace_back("  ", white, black);
  /// the clion didn't shout at me
  /// witch is odd
}

Scml::Scml(const Scml &other) {

  hc_ = GetStdHandle(STD_OUTPUT_HANDLE);
  _setmode(_fileno(stdout), _O_U16TEXT);

  buffer_ = other.buffer_;
  current_evaluation_ = other.current_evaluation_;
}

Scml &Scml::operator=(const Scml &other) {
  if (this == &other)
    return *this;

  hc_ = GetStdHandle(STD_OUTPUT_HANDLE);
  _setmode(_fileno(stdout), _O_U16TEXT);

  buffer_ = other.buffer_;
  current_evaluation_ = other.current_evaluation_;
  return *this;
}

void Scml::Clear() {
  for (auto &i : buffer_) {
    for (auto &j : i) {
      j.image = ' ';
      j.text_color = col::WHITE;
      j.background_color = col::BLACK;
    }
  }
}

void Scml::SetPixel(unsigned px, unsigned py, icon new_pixel) {
  assert(py < h_ && px < w_);
  buffer_[py][px] = new_pixel;
}

void Scml::UpdateScreen() {

  COORD c;

  c.X = 0;
  c.Y = 0;

  SetConsoleCursorPosition(hc_, c);

  for (int x = 0; x < h_; x++) {
    for (int y = 0; y < w_; y++) {

      auto text_color = buffer_[x][y].text_color;
      auto background_color = buffer_[x][y].background_color;

      std::wcout << cc(text_color, background_color);
      /// don't forget that space brother
      std::wcout << buffer_[x][y].image << ' ';
    }
    std::wcout << " \n";
  }

  SetConsoleCursorPosition(hc_, {(short)((w_ * 2) + 2), 0});
  std::wcout << current_evaluation_;
}
void Scml::DisplayBoard(ChessBoard &board) {

  for (int x = 0; x < h_; x++) {

    for (int y = 0; y < w_; y++) {

      buffer_[x][y].image = (char)board.GetElement(x, y);
    }
  }
  current_evaluation_ = board.Evaluate();
}
