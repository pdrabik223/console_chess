//
// Created by studio25 on 24.07.2021.
//

#include "arrow.h"
#include <cassert>
#include <cmath>
Coord::Coord(unsigned int x, unsigned int y) : x(x), y(y) {}
bool Coord::operator==(const Coord &rhs) const {
  return x == rhs.x && y == rhs.y;
}
bool Coord::operator!=(const Coord &rhs) const { return !(rhs == *this); }

Arrow::Arrow(const Coord &from, const Coord &to, const SDL_Color &color,
             unsigned int size)
    : from_(from), to_(to), color_(color), radius_(size) {

  arm_length = 60 / 2;
  arm_angle_ = 45;
}

void Arrow::DisplayArrow(SDL_Renderer *renderer_) {

  // arrow body

  for(auto i:GenSemicircle(from_,to_))



  SDL_RenderDrawLine(renderer_, from_.x, from_.y, to_.x, to_.y);
}



std::vector<Coord> Arrow::GenSemicircle(Coord middle_point, Coord relation) {

  assert(middle_point != relation);
  // 1. generate circle around the middle_point
  std::vector<Coord> solution;
  std::vector<Coord> full_circle(GenCircle(middle_point));

  // 2. filter all points that create angle
  // relation-middle_point-questioned_point < 90°
  for (auto point : full_circle)
    if (FindAngle(relation, middle_point, point) >= 90)
      solution.emplace_back(point);

  return solution;
}

double Arrow::FindAngle(const Coord &p0, const Coord &p1, const Coord &p2) {
  double a = pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2);
  double b = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);
  double c = pow(p2.x - p0.x, 2) + pow(p2.y - p0.y, 2);
  return acos((a + b - c) / sqrt(4 * a * b));
}
std::vector<Coord> Arrow::GenCircle(Coord middle_point) {
  int x = radius_;
  int y = 0;
  int err = 0;
  std::vector<Coord> solution;
  while (x >= y) {
    solution.emplace_back(middle_point.y + y, middle_point.x + x);
    solution.emplace_back(middle_point.y + x, middle_point.x + y);
    solution.emplace_back(middle_point.y + x, middle_point.x - y);
    solution.emplace_back(middle_point.y + y, middle_point.x - x);
    solution.emplace_back(middle_point.y - y, middle_point.x - x);
    solution.emplace_back(middle_point.y - x, middle_point.x - y);
    solution.emplace_back(middle_point.y - x, middle_point.x + y);
    solution.emplace_back(middle_point.y - y, middle_point.x + x);

    if (err <= 0) {
      ++y;
      err += 2 * y + 1;
    } else {
      --x;
      err -= 2 * x + 1;
    }
  }
  return solution;
}
std::vector<Coord> Arrow::GenArmsPoints(Coord middle_point, Coord relation) {
  std::vector<Coord> solution;


  solution.emplace_back(cos(arm_angle_) * arm_length,
                        sin(arm_angle_) * arm_length);

  solution.emplace_back(cos(360 - arm_angle_) * arm_length,
                        sin(360 - arm_angle_) * arm_length);

  return solution;
}
