//
// Created by studio25 on 22.07.2021.
//

#include "button.h"

#include <string>
Button::~Button() { SDL_FreeSurface(image_); }

const SDL_Rect &Button::GetPosition() const { return position_; }

SDL_Surface *Button::GetImage() const {

  if (image_ == nullptr) {
    fprintf(stderr, "empty surface fail: %s", SDL_GetError());
    exit(1);
  }
  return image_;
}

Button::Button(const SDL_Rect &position)
    : position_(position), image_(nullptr) {}

void Button::SetImage(std::string image_path) {
  if (image_ != nullptr)
    SDL_FreeSurface(image_);

  Uint32 r_mask = 0xff000000;
  Uint32 g_mask = 0x00ff0000;
  Uint32 b_mask = 0x0000ff00;
  Uint32 a_mask = 0x000000ff;

  image_ = SDL_CreateRGBSurface(0, 64, 64, 32, r_mask, g_mask, b_mask, a_mask);

  LoadFromPpm(image_, image_path);

  if (image_ == nullptr) {
    fprintf(stderr, "SDL_CreateRGBSurface() failed: %s", SDL_GetError());
    exit(1);
  }
}
bool Button::DetectPress(int mouse_position_x, int mouse_position_y) {

  int relative_x = mouse_position_x - position_.x;
  int relative_y = mouse_position_y - position_.y;

  if (relative_x >= 0 and relative_y >= 0 and relative_x < position_.w and
      relative_y < position_.h)
    return true;
  else
    return false;
}
