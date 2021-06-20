//
// Created by studio25 on 26.05.2021.
//

#ifndef CONSOLE_CHESS_WINDOWS_CONSOLE_SCML_H_
#define CONSOLE_CHESS_WINDOWS_CONSOLE_SCML_H_

#include "icon.h"
#include "win_colors.h"
#include <chess_board.h>
#include <chrono>
#include <future>
#include <thread>
#include <vector>

/// simple console media layer
/// step between our app and device console
/// contains buffer of wchar_t values that will be displayed on screen
/// every character will be followed by space

// todo better use press detection
//  idk how much time i want to spend at it
//  i guess we'll see
//  for now it runs of getch()
//  I'll try with getline

class Scml {

public:
  Scml();

  Scml(const Scml &other);

  Scml(unsigned int width, unsigned int height);

  Scml &operator=(const Scml &other);

  void UpdateScreen();

  void UpdateDisplay(ChessBoard &board);

  void Clear();

  ~Scml() {
    std::wcout << cc(col::WHITE, col::BLACK);
    //  system("cls");
  }

  std::string GetLine();

  void SetPixel(unsigned px, unsigned py, icon new_pixel);

  void SetBackgroundColor(unsigned px, unsigned py, Color background);
  void SetTextColor(unsigned px, unsigned py, Color text);

  void SetMessage(const std::wstring &message);

  void ClearHighlight();
  std::wstring message_;

private:
  int CountLines(std::wstring &basic_string);

  const unsigned w_ = 8;
  const unsigned h_ = 8;

  std::array<std::array<icon, 8>, 8> buffer_;
  double current_evaluation_;
  int current_move_ = 0;
  HANDLE hc_;

  unsigned previous_message_length_ = 0;
};

#endif // CONSOLE_CHESS_WINDOWS_CONSOLE_SCML_H_
