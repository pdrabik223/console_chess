//
// Created by pc on 23.04.2021.
//

#ifndef CONSOLE_CHESS__MOVE_H_
#define CONSOLE_CHESS__MOVE_H_

#include <string>



class Move {
public:
  Move() : from_(0), to_(0), evaluation_(0.0){};


  Move(unsigned from, unsigned to, double evaluation)
      : from_(from), to_(to), evaluation_(evaluation){};


  Move(unsigned from, unsigned to) : from_(from), to_(to), evaluation_(0.0) {}

  std::wstring IntToChess(unsigned position) const;

  /// \brief
  /// valid move is only that witch moves somewhere
  /// \return true if the move can be made, note that it doesn't check if the
  /// move is inside board
  explicit operator bool() const { return from_ != to_; }

  explicit operator std::string() const {
    std::string temp = "from:\t";
    temp += std::to_string(from_);
    temp += " to:\t";
    temp += std::to_string(to_);
    temp += " evaluation:\t";
    temp += std::to_string(evaluation_);
    return temp;
  }

  explicit operator std::wstring() const {
    std::wstring temp = L"from:\t";
    temp += IntToChess(from_);
    temp += L" to:\t";
    temp += IntToChess(to_);
    temp += L" evaluation:\t";
    temp += std::to_wstring(evaluation_);
    return temp;
  }
  /// \note fields of the class are public!
  unsigned from_;
  unsigned to_;
  double evaluation_;
};
//
// class promote:public move{
//
//
//    char promotion;
//
//};
//// these we'll do later
//// todo derive en_passant
//// todo derive castle
//// todo promote
#endif // CONSOLE_CHESS__MOVE_H_
