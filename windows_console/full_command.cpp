//
// Created by studio25 on 18.06.2021.
//

#include "full_command.h"

full_command Parse(std::string &line) {

  if (line[0] == 'h' or line == "help")
    return {HELP};
  if (line[0] == 'q' or line == "quit") {
    return {QUIT};
  }
  if (line[0] == 'a' or line.substr(0, 3) == "add") {
    // for simplification
    // king = 5
    // queen = 4
    // rook = 3
    // bishop = 2
    // night = 1
    // pawn = 0

    // todo add all
  }
  if (line[0] == 'd' or line.substr(0, 3) == "del") {
    if (line.substr(0, 6) == "delete")
      line.erase(0, 6);
    // todo delete all
  }
  if ((line[0] == 's' and line[1] == ' ') or
      line.substr(0, 10) == "show moves") {
  }
  return {NONE};
}
std::istream &operator>>(std::istream &in, full_command &me) {
  std::string line;
  getline(in, line);
  me = Parse(line);
  return in;
}
