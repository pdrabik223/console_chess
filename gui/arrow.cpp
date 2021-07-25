//
// Created by studio25 on 24.07.2021.
//

#include "arrow.h"
#include <cassert>
#include <cmath>
#include <iostream>
Coord::Coord(unsigned int x, unsigned int y) : x(x), y(y) {}
bool Coord::operator==(const Coord &rhs) const {
  return x == rhs.x && y == rhs.y;
}
bool Coord::operator!=(const Coord &rhs) const { return !(rhs == *this); }
Coord::Coord() : x(0), y(0) {}

Arrow::Arrow(const Coord &from, const Coord &to, const SDL_Color &color,
             unsigned int size)
    : from_(from), to_(to), color_(color), radius_(size) {

  arm_length = 60 / 2;
  arm_angle_ = 45;
}

void Arrow::DisplayArrow(SDL_Renderer *renderer_, bool flip_axis,
                         unsigned window_height) {

  // arrow body

  Coord temp_from = from_;
  Coord temp_to = to_;

  if (flip_axis) {
    temp_from.y = window_height - temp_from.y;
    temp_to.y = window_height - temp_to.y;
  }

  std::vector<Coord> from_semicircle = GenSemicircle(temp_from, temp_to);
  std::vector<Coord> to_semicircle = GenSemicircle(temp_to, temp_from);
  // assert(from_semicircle.size() == to_semicircle.size());

  SDL_SetRenderDrawColor(renderer_, color_.r, color_.g, color_.b, color_.a);
  // I thing these need to be sorted first
  auto range = to_semicircle.size() < from_semicircle.size()
                   ? to_semicircle.size()
                   : from_semicircle.size();
  for (int i = 0; i < range; i++) {
    SDL_RenderDrawLine(renderer_, from_semicircle[i].x, from_semicircle[i].y,
                       to_semicircle[i].x, to_semicircle[i].y);
  }
}

std::vector<Coord> Arrow::GenSemicircle(Coord middle_point, Coord relation) {
  assert(middle_point != relation);

  // 1. generate circle around the middle_point
  std::vector<Coord> solution;
  std::vector<Coord> full_circle(GenCircle(middle_point));

  std::cout << " " << full_circle.size() << std::endl;
  // 2. filter all points that create angle
  // relation-middle_point-questioned_point < 90°
  for (auto point : full_circle)
    if (FindAngle(relation, middle_point, point) >= (double)(3.141527 / 2))
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
