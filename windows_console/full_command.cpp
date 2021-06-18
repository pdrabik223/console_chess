//
// Created by studio25 on 18.06.2021.
//

#include "full_command.h"
int ChessToInt(std::string coord) {

  if (coord[0] == ' ') {
    while (coord[0] != ' ')
      coord.erase(coord.begin());
    coord.erase(coord.begin());
  }

  auto cut = coord.substr(0, 2);
  coord.erase(0, 2);

  switch (cut[0]) {
  case 'a':
    return (B_HEIGHT - coord[1]) * B_HEIGHT + 0;
  case 'b':
    return (B_HEIGHT - coord[1]) * B_HEIGHT + 1;
  case 'c':
    return (B_HEIGHT - coord[1]) * B_HEIGHT + 2;
  case 'd':
    return (B_HEIGHT - coord[1]) * B_HEIGHT + 3;
  case 'e':
    return (B_HEIGHT - coord[1]) * B_HEIGHT + 4;
  case 'f':
    return (B_HEIGHT - coord[1]) * B_HEIGHT + 5;
  case 'g':
    return (B_HEIGHT - coord[1]) * B_HEIGHT + 6;
  case 'h':
    return (B_HEIGHT - coord[1]) * B_HEIGHT + 7;
  default:
    return -1;
  }
}

full_command Parse(std::string &line) {

  if (line == "help")
    return {HELP};
  if (line == "quit") {
    return {QUIT};
  }
  if (line.substr(0, 3) == "add") {

    while (line[0] != ' ')
      line.erase(line.begin());
    line.erase(line.begin());

    // for simplification
    // king = 5
    // queen = 4
    // rook = 3
    // bishop = 2
    // night = 1
    // pawn = 0

    // todo add all
  }

  if (line.substr(0, 3) == "del") {

    while (line[0] != ' ')
      line.erase(line.begin());
    line.erase(line.begin());

    if (line == "all")
      return {DELL_ALL};

    std::vector<int> data;
    data.push_back(ChessToInt(line));

    return {DELETE_PIECE, data};
  }

  if ((line[0] == 's' and line[1] == ' ') or
      line.substr(0, 10) == "show moves") {
  }

  switch (line[0]) {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
    break;
 //   Show(ChessToInt(coord));
  }
  return {NONE};
}
std::istream &operator>>(std::istream &in, full_command &me) {
  std::string line;
  getline(in, line);
  me = Parse(line);
  return in;
}
void full_command::FromString(std::string line) {
  *this = Parse(line);
}
