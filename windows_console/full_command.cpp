//
// Created by studio25 on 18.06.2021.
//

#include "full_command.h"

void EraseTillSpace(std::string &line) {

  while (line[0] != ' ')
    line.erase(line.begin());
  line.erase(line.begin());
}

int ChessToInt(std::string &coord) {

  if (coord[0] == ' ')
    coord.erase(0, 1);

  auto cut = coord.substr(0, 2);
  coord.erase(0, 2);

  int x = (cut[1] - '0');

  switch (cut[0]) {
  case 'a':
    return ( x - 1 ) * B_WIDTH + 0;
  case 'b':
    return ( x - 1 )  * B_WIDTH + 1;
  case 'c':
    return ( x - 1 )  * B_WIDTH + 2;
  case 'd':
    return ( x - 1 )  * B_WIDTH + 3;
  case 'e':
    return ( x - 1 )  * B_WIDTH + 4;
  case 'f':
    return ( x - 1 )  * B_WIDTH + 5;
  case 'g':
    return ( x - 1 )  * B_WIDTH + 6;
  case 'h':
    return ( x - 1 )  * B_WIDTH + 7;
  default:
    return -1;
  }
}

full_command
Parse(std::string &line) {

  if (line == "help")
    return {HELP};
  if (line == "quit")
    return {QUIT};

  if(line.substr(0,5) == "clear")
    return {CLEAR};

  if (line.substr(0, 3) == "add") {
    line.erase(0, 3);
    EraseTillSpace(line);
    std::vector<int> data;

    data.push_back(ChessToInt(line));
    switch (line[0]) {
    case 'p':

      data.push_back('p');
      data.push_back(0);
      return {ADD_PIECE, data};

    case 'P':
      data.push_back('p');
      data.push_back(1);
      return {ADD_PIECE, data};

    case 'n':
      data.push_back('n');
      data.push_back(0);
      return {ADD_PIECE, data};

    case 'N':
      data.push_back('n');
      data.push_back(1);
      return {ADD_PIECE, data};

    case 'b':
      data.push_back('b');
      data.push_back(0);
      return {ADD_PIECE, data};

    case 'B':
      data.push_back('b');
      data.push_back(1);
      return {ADD_PIECE, data};

    case 'r':
      data.push_back('r');
      data.push_back(0);
      return {ADD_PIECE, data};

    case 'R':
      data.push_back('r');
      data.push_back(1);
      return {ADD_PIECE, data};

    case 'q':
      data.push_back('q');
      data.push_back(0);
      return {ADD_PIECE, data};

    case 'Q':
      data.push_back('q');
      data.push_back(1);
      return {ADD_PIECE, data};

    case 'k':
      data.push_back('k');
      data.push_back(0);
      return {ADD_PIECE, data};

    case 'K':
      data.push_back('k');
      data.push_back(1);
      return {ADD_PIECE, data};
    }

    // for simplification
    // king = k
    // queen = q
    // rook = r
    // bishop = b
    // night = n
    // pawn = p
  }

  if (line.substr(0, 3) == "del") {

    EraseTillSpace(line);

    if (line == "all")
      return {DELL_ALL};

    std::vector<int> data;
    data.push_back(ChessToInt(line));

    return {DELETE_PIECE, data};
  }

  if (line.substr(0, 4) == "show") {

    EraseTillSpace(line);

    if (line == "all")
      return {SHOW_ALL};

    std::vector<int> data;
    data.push_back(ChessToInt(line));

    return {SHOW_MOVES, data};
  }




  if (line.substr(0, 4) == "move") {
    EraseTillSpace(line);

    std::vector<int> data;
    data.push_back(ChessToInt(line));
    data.push_back(ChessToInt(line));

    return {MOVE, data};
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
    std::vector<int> moves;
    moves.push_back(ChessToInt(line));
    return {SHOW_MOVES, moves};
  }
  return {NONE};
}

void full_command::FromString(std::string line) { *this = Parse(line); }
