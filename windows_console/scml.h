//
// Created by studio25 on 26.05.2021.
//

#ifndef BLOCK_O_AUTOMATA_SCML_H
#define BLOCK_O_AUTOMATA_SCML_H

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
    system("cls");
  }

private:
  void SetPixel(unsigned px, unsigned py, icon new_pixel);

  const unsigned w_ = 8;
  const unsigned h_ = 8;

  std::array<std::array<icon, 8>, 8> buffer_;
  double current_evaluation_;
  HANDLE hc_;
};

#endif // BLOCK_O_AUTOMATA_SCML_H
