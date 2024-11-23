#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "GameConstants.h"

class Score {
 public:
  Score();
  void updateScore();
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);

 private:
  SDL_Rect foodSourceRect;
  SDL_Rect rect;
  int score;
};
#endif
