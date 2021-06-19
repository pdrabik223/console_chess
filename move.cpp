//
// Created by pc on 23.04.2021.
//

#include "move.h"
std::wstring Move::IntToChess(unsigned position) const {
  unsigned number = position / 8;
  unsigned letter = position % 8;
  letter += 'a';

  std::wstring temp = (wchar_t)letter + std::to_wstring(number + 1);

  return temp;
}
bool Move::operator==(const Move &rhs) const {
  return evaluation_ == rhs.evaluation_;
}
bool Move::operator!=(const Move &rhs) const {
  return evaluation_ != rhs.evaluation_;
}
bool Move::operator<(const Move &rhs) const {
  return evaluation_ < rhs.evaluation_;
}
bool Move::operator>(const Move &rhs) const {
  return evaluation_ > rhs.evaluation_;
}
bool Move::operator<=(const Move &rhs) const {
  return evaluation_ <= rhs.evaluation_;
}
bool Move::operator>=(const Move &rhs) const {
  return evaluation_ >= rhs.evaluation_;
}
