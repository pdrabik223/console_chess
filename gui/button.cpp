//
// Created by studio25 on 22.07.2021.
//

#include "button.h"

#include <string>
Button::~Button() { delete image_; }

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
bool Button::DetectPress(SDL_Rect cursor_position) {
  if (cursor_position.x >= position_.x and cursor_position.y >= position_.y and
      cursor_position.w < position_.w and cursor_position.h < position_.h)
    return true;
  else
    return false;
}
