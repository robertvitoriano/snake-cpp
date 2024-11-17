#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <vector>

#include "Food.h"
#include "Renderer.h"
#include "Snake.h"

class Game {
 public:
  Game();
  ~Game();
  void run();

 private:
  Snake snake;
  Food food;
  SDL_Window *window;
  SDL_Renderer *gameRenderer;
  Renderer renderer;
  SDL_Texture *spritesheetTexture;
  SDL_Texture *backgroundTexture;
  bool running;
  void processInput();
  void handleFoodEating();
  void update();
  void render();
  bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);
};

#endif
