#ifndef GAME_H
#define GAME_H

#include "Food.h"
#include "Snake.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

class Game {
public:
  Game();
  ~Game();
  void run();

private:
  Snake snake;
  Food food;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *spritesheetTexture;

  bool running;
  void processInput();
  void handleFoodEating();
  void update();
  void render();
  bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);
};

#endif
