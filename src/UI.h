#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>

#include <string>

#include "GameConstants.h"
#include "Graphics.h"

class UI {
 public:
  UI();
  void updateScore();
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture, SDL_Texture *heartTexture);
  bool hasLost();
  void setLives(int snakeLives);

 private:
  SDL_Rect foodSourceRect;
  SDL_Rect rect;
  Graphics gameRenderer;
  int score;
  int lives;
};
#endif
