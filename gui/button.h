//
// Created by studio25 on 22.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_BUTTON_H_
#define CONSOLE_CHESS_GUI_BUTTON_H_
#include <ciso646> // for "and" ,  "or"  etc. symbols
#include "ppm_loader.h"
#include <SDL_surface.h>
#include <string>
class Button {
public:
  Button():position_({0, 0, 0, 0}),image_(nullptr){};

  Button(const SDL_Rect &position);

  bool DetectPress(SDL_Rect cursor_position);

  void SetImage(std::string image_path);

  const SDL_Rect &GetPosition() const;

  SDL_Surface *GetImage() const;

  virtual ~Button();

private:

  SDL_Rect position_;
  SDL_Surface * image_;

};

#endif // CONSOLE_CHESS_GUI_BUTTON_H_
