//
// Created by studio25 on 18.06.2021.
//

#ifndef CONSOLE_CHESS_WINDOWS_CONSOLE_FULL_COMMAND_H_
#define CONSOLE_CHESS_WINDOWS_CONSOLE_FULL_COMMAND_H_

#include <vector>
#include <windows_console/scml.h>

enum Task {

  QUIT,
  MOVE,
  ADD_PIECE,
  ADD_ALL,
  DELETE_PIECE,
  DELL_ALL, // todo finish them
  //  i have 6 h of sleep to cath
  SHOW_MOVES,
  SHOW_ALL,
  NONE,
  HELP

};

struct full_command;

full_command Parse(std::string &line);

struct full_command {
  full_command() : comm(NONE), data(){};
  full_command(Task t) : comm(t){};

  full_command(Task t, std::vector<int> data)
      : comm(t), data(std::move(data)){};

  bool operator==(const Task &rhs) const { return comm == rhs; }
  bool operator!=(const Task &rhs) const { return rhs != comm; }

//  friend std::istream &operator>>(std::istream &in, full_command &me);

  void FromString(std::string line);

  Task comm;
  std::vector<int> data;
};

#endif // CONSOLE_CHESS_WINDOWS_CONSOLE_FULL_COMMAND_H_
