#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Paddle.h"
#include <SDL2/SDL.h>

class Game {
public:
  Game();
  ~Game();
  void run();

private:
  Paddle playerPaddle;
  Paddle aiPaddle;
  Ball ball;
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool running;

  void processInput();
  void update();
  void render();
  static bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);
};

#endif
