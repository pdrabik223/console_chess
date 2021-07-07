//
// Created by studio25 on 07.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_BUTTON_H_
#define CONSOLE_CHESS_GUI_BUTTON_H_

#include <SDL_rect.h>
#include <SDL_surface.h>
#include <SDL_render.h>


class Button {

  SDL_Rect placement_;
  SDL_Surface* image_ = SDL_LoadBMP("image.bmp");


  void DrawToRenderer(SDL_Renderer *renderer);
~Button(){


  SDL_FreeSurface(image_);
}
};

#endif // CONSOLE_CHESS_GUI_BUTTON_H_
