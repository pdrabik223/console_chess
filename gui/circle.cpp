//
// Created by studio25 on 26.07.2021.
//

#include "circle.h"
Circle::Circle(const Coord &center, SDL_Color color, unsigned int radius,
               unsigned int width)
    : center_(center), radius_(radius), width_(width), color_(color) {}

std::vector<Coord> Circle::GenCircle(Coord middle_point, unsigned int radius) {
  int x = radius;
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
void Circle::DisplayCircle(SDL_Renderer *renderer, bool flip_axis,
                           unsigned int window_height) {
  Coord center_copy = center_;

  if (flip_axis) {
    center_copy.x = window_height - center_copy.x;
  }
  SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);

  for (int w = 0; w < width_; ++w)
    for (auto c : GenCircle(center_copy,radius_-w))
      SDL_RenderDrawPoint(renderer,c.x,c.y);


}
