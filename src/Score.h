#ifndef SCORE_H
#define SCORE_H
#include <SDL2/SDL.h>

#include "GameConstants.h"

class Score {
 public:
  Score();
  void updateScore();
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);

 private:
  SDL_Rect foodSourceRect;
  SDL_Rect rect;
};
#endif
