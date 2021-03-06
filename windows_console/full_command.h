//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_WINDOWS_CONSOLE_FULL_COMMAND_H_
#define CONSOLE_CHESS_WINDOWS_CONSOLE_FULL_COMMAND_H_

#include <vector>
#include <windows_console/scml.h>

enum class Task {

  QUIT, // ok
  MOVE,
  ADD_PIECE,
  ADD_ALL,
  DELETE_PIECE,
  DELL_ALL,
  SHOW_MOVES,
  SHOW_ALL,
  MINMAX,
  MINMAX_ALL,
  ALFA_BETA_MINMAX,
  ALFA_BETA_MINMAX_ALL,
  ALFA_BETA_MINMAX_W_TRANSPOSITION_TABLE_ALL,
  ALFA_BETA_MINMAX_W_TRANSPOSITION_TABLE,
  NONE,
  CLEAR,
  LOAD,
  EPIC_COMPUTER_FIGHT,
  HELP // ok

};

class full_command {
public:
  full_command() : comm(Task::NONE), data(){};
  full_command(Task t) : comm(t){};

  full_command(Task t, std::vector<int> data)
      : comm(t), data(std::move(data)){};

  bool operator==(const Task &rhs) const { return comm == rhs; }
  bool operator!=(const Task &rhs) const { return rhs != comm; }

  void FromString(std::string line);

private:
  static full_command Add(std::string &line);

  static full_command Del(std::string &line);

  static full_command Show(std::string &line);

  static full_command MinMax(std::string &line);

  static full_command AlphaBetaMinMax(std::string &line);

  static full_command AlphaBetaMinMaxTranspositionTable(std::string &line);

  static full_command Move(std::string &line);

  static full_command Fight(std::string &line);

  full_command Parse(std::string &line);
public:
  Task comm;
  std::vector<int> data;
};

full_command Parse(std::string &line);

#endif // CONSOLE_CHESS_WINDOWS_CONSOLE_FULL_COMMAND_H_
