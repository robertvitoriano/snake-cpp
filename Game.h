#ifndef GAME_H
#define GAME_H

#include "Food.h"
#include "Snake.h"
#include <SDL2/SDL.h>
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
  bool running;

  void processInput();
  void update();
  void render();
  static bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);
};

#endif
