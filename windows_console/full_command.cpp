//
// Created by studio25 on 18.06.2021.
//

#include "full_command.h"

void EraseTillSpace(std::string &line) {

  while (line[0] != ' ' && !line.empty())
    line.erase(line.begin());

  if (!line.empty())
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
    return (x - 1) * B_WIDTH + 0;
  case 'b':
    return (x - 1) * B_WIDTH + 1;
  case 'c':
    return (x - 1) * B_WIDTH + 2;
  case 'd':
    return (x - 1) * B_WIDTH + 3;
  case 'e':
    return (x - 1) * B_WIDTH + 4;
  case 'f':
    return (x - 1) * B_WIDTH + 5;
  case 'g':
    return (x - 1) * B_WIDTH + 6;
  case 'h':
    return (x - 1) * B_WIDTH + 7;
  default:
    return -1;
  }
}

full_command full_command::Add(std::string &line) {
  line.erase(0, 3);
  EraseTillSpace(line);
  std::vector<int> data;

  data.push_back(ChessToInt(line));
  EraseTillSpace(line);

  switch (line[0]) {
  case 'p':

    data.push_back('p');
    data.push_back(0);
    return {Task::ADD_PIECE, data};

  case 'P':
    data.push_back('p');
    data.push_back(1);
    return {Task::ADD_PIECE, data};

  case 'n':
    data.push_back('n');
    data.push_back(0);
    return {Task::ADD_PIECE, data};

  case 'N':
    data.push_back('n');
    data.push_back(1);
    return {Task::ADD_PIECE, data};

  case 'b':
    data.push_back('b');
    data.push_back(0);
    return {Task::ADD_PIECE, data};

  case 'B':
    data.push_back('b');
    data.push_back(1);
    return {Task::ADD_PIECE, data};

  case 'r':
    data.push_back('r');
    data.push_back(0);
    return {Task::ADD_PIECE, data};

  case 'R':
    data.push_back('r');
    data.push_back(1);
    return {Task::ADD_PIECE, data};

  case 'q':
    data.push_back('q');
    data.push_back(0);
    return {Task::ADD_PIECE, data};

  case 'Q':
    data.push_back('q');
    data.push_back(1);
    return {Task::ADD_PIECE, data};

  case 'k':
    data.push_back('k');
    data.push_back(0);
    return {Task::ADD_PIECE, data};

  case 'K':
    data.push_back('k');
    data.push_back(1);
    return {Task::ADD_PIECE, data};
  }
  printf("command error");
  return {Task::NONE};
}

full_command full_command::Del(std::string &line) {

  EraseTillSpace(line);

  if (line == "all")
    return {Task::DELL_ALL};

  std::vector<int> data;
  data.push_back(ChessToInt(line));
  if (data.front() == -1) {
    printf("command error");
    return {Task::NONE};
  }

  return {Task::DELETE_PIECE, data};
}

full_command full_command::Show(std::string &line) {
  EraseTillSpace(line);

  if (line == "all")
    return {Task::SHOW_ALL};

  std::vector<int> data;
  data.push_back(ChessToInt(line));

  if (data.front() != -1)
    return {Task::SHOW_MOVES, data};
  printf("command error");
  return {Task::NONE};
}

full_command full_command::MinMax(std::string &line) {

  EraseTillSpace(line);

  full_command temp;
  std::vector<int> data;

  if (line.substr(0, 3) == "all") {

    temp.comm = Task::MINMAX_ALL;

    EraseTillSpace(line);

    if (line.substr(0, 5) == "white")
      data.push_back(1);
    else if (line.substr(0, 5) == "black")
      data.push_back(0);
    else {
      printf("command error");
      return {Task::NONE};
    }
    EraseTillSpace(line);
    data.push_back(std::stoi(line));
    temp.data = data;

  } else {
    temp.comm = Task::MINMAX;
    data.push_back(ChessToInt(line));

    if (data.front() == -1) {
      printf("command error");
      return {Task::NONE};
    }

    EraseTillSpace(line);
    data.push_back(std::stoi(line));
    temp.data = data;
  }

  return temp;
}

full_command full_command::AlphaBetaMinMax(std::string &line) {
  EraseTillSpace(line);

  full_command temp;
  std::vector<int> data;

  if (line.substr(0, 3) == "all") {

    temp.comm = Task::MINMAX_ALL;

    EraseTillSpace(line);

    if (line.substr(0, 5) == "white")
      data.push_back(1);
    else if (line.substr(0, 5) == "black")
      data.push_back(0);
    else {
      printf("command error");
      return {Task::NONE};
    }
    EraseTillSpace(line);
    data.push_back(std::stoi(line));
    temp.data = data;

  } else {
    temp.comm = Task::ALFA_BETA_MINMAX;
    data.push_back(ChessToInt(line));

    if (data.front() == -1) {
      printf("command error");
      return {Task::NONE};
    }

    EraseTillSpace(line);
    data.push_back(std::stoi(line));
    temp.data = data;
  }

  return temp;
}

full_command
full_command::AlphaBetaMinMaxTranspositionTable(std::string &line) {
  EraseTillSpace(line);

  full_command temp;
  std::vector<int> data;

  if (line.substr(0, 3) == "all") {

    temp.comm = Task::ALFA_BETA_MINMAX_W_TRANSPOSITION_TABLE_ALL;

    EraseTillSpace(line);

    if (line.substr(0, 5) == "white")
      data.push_back(1);
    else if (line.substr(0, 5) == "black")
      data.push_back(0);
    else {
      printf("command error");
      return {Task::NONE};
    }

    EraseTillSpace(line);
    data.push_back(std::stoi(line));
    temp.data = data;

  } else {
    temp.comm = Task::ALFA_BETA_MINMAX_W_TRANSPOSITION_TABLE;
    data.push_back(ChessToInt(line));
    if (data.front() == -1) {
      printf("command error");
      return {Task::NONE};
    }


    EraseTillSpace(line);
    data.push_back(std::stoi(line));
    temp.data = data;
  }

  return temp;
}

full_command full_command::Move(std::string &line) {
  EraseTillSpace(line);

  std::vector<int> data;
  data.push_back(ChessToInt(line));
  if (data[0] == -1) {
    printf("command error");
    return {Task::NONE};
  }
  data.push_back(ChessToInt(line));
  if (data[1] == -1) {
    printf("command error");
    return {Task::NONE};
  }
  return {Task::MOVE, data};
}

full_command full_command::Fight(std::string &line) {
  EraseTillSpace(line);
  std::vector<int> data;

  /// white brain
  if (line.substr(0, 6) == "minmax") {
    EraseTillSpace(line);
    data.push_back((int)Task::MINMAX);
    data.push_back(std::stoi(line));
    EraseTillSpace(line);
  } else if (line.substr(0, 8) == "abminmax") {
    EraseTillSpace(line);
    data.push_back((int)Task::ALFA_BETA_MINMAX);
    data.push_back(std::stoi(line));
    EraseTillSpace(line);
  }else {
    printf("command error");
    return {Task::NONE};
  }

  data.push_back(1); // threads
  /// black brain
  if (line.substr(0, 6) == "minmax") {
    EraseTillSpace(line);
    data.push_back((int)Task::MINMAX);
    data.push_back(std::stoi(line));
    EraseTillSpace(line);
  } else if (line.substr(0, 8) == "abminmax") {
    EraseTillSpace(line);
    data.push_back((int)Task::ALFA_BETA_MINMAX);
    data.push_back(std::stoi(line));
    EraseTillSpace(line);
  }else {
    printf("command error");
    return {Task::NONE};
  }

  data.push_back(1); // threads

  return {Task::EPIC_COMPUTER_FIGHT, data};
}

full_command full_command::Parse(std::string &line) {

  if (line == "help")
    return {Task::HELP};
  if (line == "quit")
    return {Task::QUIT};

  if (line.substr(0, 5) == "clear")
    return {Task::CLEAR};

  if (line.substr(0, 3) == "add")
    return Add(line);

  if (line.substr(0, 3) == "del")
    return Del(line);

  if (line.substr(0, 4) == "show")
    return Show(line);

  if (line.substr(0, 6) == "minmax")
    return MinMax(line);

  if (line.substr(0, 8) == "abminmax")
    return AlphaBetaMinMax(line);

  if (line.substr(0, 10) == "abminmaxtt")
    return AlphaBetaMinMaxTranspositionTable(line);

  if (line.substr(0, 4) == "move")
    return Move(line);

  if (line.substr(0, 6) == "fight!")
    return Fight(line);

  if (line.substr(0, 4) == "load")
    return {Task::LOAD};

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
    return {Task::SHOW_MOVES, moves};
  }
  return {Task::NONE};
}

void full_command::FromString(std::string line) { *this = Parse(line); }
