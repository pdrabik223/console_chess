//
// Created by studio25 on 26.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_CIRCLE_H_
#define CONSOLE_CHESS_GUI_CIRCLE_H_
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <vector>
#include <ciso646>
#include "arrow.h"
class Circle {
public:
  Circle(const Coord &center, SDL_Color color, unsigned int radius,
         unsigned int width);
  void DisplayCircle(SDL_Renderer *renderer,bool flip_axis, unsigned window_height);

private:
  std::vector<Coord> GenCircle(Coord middle_point,unsigned radius);
protected:
  SDL_Color color_;
  Coord center_;
  unsigned radius_;
  unsigned width_;
};

#endif // CONSOLE_CHESS_GUI_CIRCLE_H_
