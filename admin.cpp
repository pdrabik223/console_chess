//
// Created by studio25 on 18.06.2021.
//

#include "admin.h"



int ChessToInt(std::string coord) {

  switch (coord[0]) {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
    return (B_HEIGHT - coord[1] + 1) * B_HEIGHT + coord[3] - 1;
  default:
    return -1;
  }
}



full_command Decode(std::string input);
void RunTask(ChessBoard &game, full_command input);
