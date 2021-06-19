//
// Created by studio25 on 26.05.2021.
//

#include "scml.h"
#include <cassert>
#include <string>

int CountLines(const std::wstring &basic_string) {
  int counter = 0;
  for (int i : basic_string)
    if (i == '\n')
      counter++;
  return counter;
}

Scml::Scml() {

  hc_ = GetStdHandle(STD_OUTPUT_HANDLE);
  _setmode(_fileno(stdout), _O_U16TEXT);

  for (int y = 0; y < h_; y++) {

    for (int x = 0; x < w_; x++) {
      col::Color background;
      col::Color text = col::BLACK;
      if (y % 2 == 0 xor x % 2 == 0)
        background = col::GRAY;
      else
        background = col::WHITE;

      buffer_[y][x] = {' ', text, background};
    }
  }

  current_evaluation_ = 0;

  /// here when I wrote    buffer.emplace_back("  ", white, black);
  /// the clion didn't shout at me
  /// witch is odd
  message_ = {};
  system("cls");
}

Scml::Scml(const Scml &other) {

  hc_ = GetStdHandle(STD_OUTPUT_HANDLE);
  _setmode(_fileno(stdout), _O_U16TEXT);

  buffer_ = other.buffer_;
  current_evaluation_ = other.current_evaluation_;
  message_ = {};
  system("cls");
}

Scml &Scml::operator=(const Scml &other) {
  if (this == &other)
    return *this;

  hc_ = GetStdHandle(STD_OUTPUT_HANDLE);
  _setmode(_fileno(stdout), _O_U16TEXT);

  buffer_ = other.buffer_;
  current_evaluation_ = other.current_evaluation_;
  message_ = other.message_;
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
  message_ = {};
}

void Scml::SetPixel(unsigned px, unsigned py, icon new_pixel) {
  assert(py < h_ && px < w_);
  buffer_[py][px] = new_pixel;
}

wchar_t ToUnicode(char piece_icon) {
  switch (piece_icon) {
  case 'p':
    //   return 9817;
  case 'P':
    return 9823;

  case 'n':
  //  return 9816;
  case 'N':
    return 9822;

  case 'b':
  //  return 9815;
  case 'B':
    return 9821;

  case 'r':
    // return 9814;
  case 'R':
    return 9820;

  case 'q':
    //   return 9813;
  case 'Q':
    return 9819;

  case 'k':
  //  return 9812;
  case 'K':
    return 9818;

  case ' ':
    return ' ';
  }
  assert(false);
  return ';';
}
void Scml::UpdateScreen() {

  COORD c;

  c.X = 0;
  c.Y = 0;

  SetConsoleCursorPosition(hc_, c);

  for (int x = 0; x < h_; x++) {
    std::wcout << cc(col::WHITE, col::BLACK) << x + 1 << " ";
    for (int y = 0; y < w_; y++) {

      auto text_color = buffer_[x][y].text_color;
      auto background_color = buffer_[x][y].background_color;

      std::wcout << cc(text_color, background_color);
      /// don't forget that space brother
      std::wcout << ToUnicode(buffer_[x][y].image) << ' ';
    }
    std::wcout << "\n";
  }
  std::wcout << cc(col::WHITE, col::BLACK) << "  a b c d e f g h\n";

  SetConsoleCursorPosition(hc_, {(short)((w_ * 2) + 2), 0});

  std::wcout << current_evaluation_;
  SetConsoleCursorPosition(hc_, {0, 9});
  for (int i = 0; i < previous_message_length_; i++)
    std::wcout
        << L"                                                               "
           "                            \n";
  SetConsoleCursorPosition(hc_, {0, 9});

  std::wcout << cc(col::WHITE, col::BLACK) << message_;
  previous_message_length_ = CountLines(message_);
  message_ = L"";
}

void Scml::UpdateDisplay(ChessBoard &board) {

  for (int x = 0; x < h_; x++) {

    for (int y = 0; y < w_; y++) {

      buffer_[x][y].image = (char)board.GetElement(x, y);
      if (board.GetElement(x, y).Color())
        buffer_[x][y].text_color = col::BRIGHT_WHITE;
      else
        buffer_[x][y].text_color = col::BLACK;
    }
  }
  current_evaluation_ = board.Evaluate();
  message_ = {};
}

void Scml::SetBackgroundColor(unsigned int px, unsigned int py,
                              Color background) {
  buffer_[px][py].background_color = background;
}

void Scml::SetTextColor(unsigned int px, unsigned int py, Color text) {
  buffer_[px][py].text_color = text;
}

std::string Scml::GetLine() {
  std::string input;

  std::wcout << L">";
  getline(std::cin, input);
  SetConsoleCursorPosition(hc_, {0, (short)(9 + previous_message_length_)});
  std::wcout << L"\r" << L"                                               ";

  return input;
}

void Scml::SetMessage(const std::wstring &message) { message_ = message; }
void Scml::ClearHighlight() {

  col::Color background;
  for (int y = 0; y < h_; y++) {

    for (int x = 0; x < w_; x++) {
      if (y % 2 == 0 xor x % 2 == 0)
        background = col::GRAY;
      else
        background = col::WHITE;
      buffer_[y][x].background_color = background;
    }
  }
}
