//
// Created by studio25 on 26.05.2021.
//

#ifndef CONSOLE_CHESS_WINDOWS_CONSOLE_ICON_H_
#define CONSOLE_CHESS_WINDOWS_CONSOLE_ICON_H_

#include "win_colors.h"
using namespace col;

struct icon {
  icon();

  icon(wchar_t image, Color icon_color);

  icon(wchar_t image, Color text_color, Color background_color);

  wchar_t image;
  Color text_color;
  Color background_color;

  bool operator==(const icon &rhs) const;

  bool operator!=(const icon &rhs) const;
};

#endif // CONSOLE_CHESS_WINDOWS_CONSOLE_ICON_H_
