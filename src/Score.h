#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL.h>

#include <string>

#include "GameConstants.h"
#include "Renderer.h"

class Score {
 public:
  Score();
  void updateScore();
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  bool hasLost();

 private:
  SDL_Rect foodSourceRect;
  SDL_Rect rect;
  Renderer gameRenderer;
  int score;
};
#endif
