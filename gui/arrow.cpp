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

void Arrow::DisplayArrow(SDL_Renderer *renderer, bool flip_axis,
                         unsigned window_height) {

  // arrow body

  Coord temp_from = from_;
  Coord temp_to = to_;

  if (flip_axis) {
    temp_from.x = window_height - temp_from.x;
    temp_to.x = window_height - temp_to.x;
  }

  std::vector<Coord> from_semicircle = GenCircle(temp_from);
  std::vector<Coord> to_semicircle = GenCircle(temp_to);
  // assert(from_semicircle.size() == to_semicircle.size());

  SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);

  for (int i = 0; i < to_semicircle.size(); i++) {
    SDL_RenderDrawLine(renderer, from_semicircle[i].x, from_semicircle[i].y,
                       to_semicircle[i].x, to_semicircle[i].y);
  }
// todo finish arrows add arms and cut number of drawn lines by half, also gradient to redeem yourself


}

std::vector<Coord> Arrow::GenSemicircle(Coord middle_point, Coord relation) {
  assert(middle_point != relation);

  // 1. generate circle around the middle_point
  std::vector<Coord> solution;
  std::vector<Coord> full_circle(GenCircle(middle_point));

  // 2. filter all points that create angle
  // relation-middle_point-questioned_point < 90°
  for (const Coord &point : full_circle) {

    double angle = FindAngle(point, middle_point, relation);

    if (angle >= (double)(3.141571 / 2.0) and angle <= (double)(3.141571 * 1.5))
      solution.emplace_back(point);
  }
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

std::vector<Coord> Arrow::GenArmsPoints(Coord from_point, Coord to_point) {
  std::vector<Coord> solution;

  solution.emplace_back(from_point.x + cos(arm_angle_) * arm_length,
                        from_point.y + sin(arm_angle_) * arm_length);

  solution.emplace_back(from_point);

  //  solution.emplace_back(cos(360 - arm_angle_) * arm_length,
  //                        sin(360 - arm_angle_) * arm_length);

  return solution;
}
