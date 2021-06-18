//
// Created by pc on 05.05.2021.
//

#ifndef BLOCK_O_AUTOMATA_WIN_COLLORS_H
#define BLOCK_O_AUTOMATA_WIN_COLORS_H
#ifdef WIN32
#include <Windows.h>

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdio.h> /// for unicode purposes

#pragma once
 namespace col {
  enum Color {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    AQUA = 3,
    RED = 4,
    PURPLE = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_AQUA = 11,
    LIGHT_RED = 12,
    LIGHT_PURPLE = 13,
    LIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15

  };
};
/// console color
/// changes the console colors to given in constructor
using namespace col;
struct cc {

  cc(Color text, Color background);
  cc(Color text);

  friend std::ostream &operator<<(std::ostream &out, const cc &ref);
  friend std::wostream &operator<<(std::wostream &out, const cc &ref);


 Color text;
  Color background;
};

#endif
#endif // BLOCK_O_AUTOMATA_WIN_COLORS_H
