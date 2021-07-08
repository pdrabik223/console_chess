//
// Created by studio25 on 07.07.2021.
//

#ifndef CONSOLE_CHESS_GUI_BUTTON_H_
#define CONSOLE_CHESS_GUI_BUTTON_H_

#include "ppm_loader.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <map>
#include <pawns/piece.h>

static std::array<SDL_Surface,SIZE - 1> images;
static void LoadImages(){
  LoadFromPpm (images[WHITE_PAWN], "assets/white_pawn.ppm");

}

class Button {

public:
  Button() {

    placement_ = {0, 0, 10, 10};

  }


  void DrawToRenderer(SDL_Renderer *renderer, SDL_Rect target_placement);

  void LoadImage(std::string path){

    SDL_FreeSurface(&image_);
    LoadFromPpm(image_,path);

  }

  void LoadImage(PieceType piece_id){

    SDL_FreeSurface(&image_);

    image_.pixels = new void*(images[piece_id].pixels);

  }

  ~Button() { SDL_FreeSurface(&image_); }

protected:
  SDL_Rect placement_;
  SDL_Surface image_;
};

#endif // CONSOLE_CHESS_GUI_BUTTON_H_
