//
// Created by studio25 on 07.07.2021.
//

#include "button.h"
void Button::DrawToRenderer(SDL_Renderer *renderer) {

  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image_);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_DestroyTexture(texture);

}
