#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <string>
#include <vector>

#include "Food.h"
#include "MusicPlayer.h"
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
  MusicPlayer musicPlayer;
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
