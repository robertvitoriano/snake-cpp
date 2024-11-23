#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <string>
#include <vector>

#include "Food.h"
#include "MusicPlayer.h"
#include "Renderer.h"
#include "Score.h"
#include "Snake.h"
class Game {
 public:
  Game();
  ~Game();
  void run();

 private:
  Snake snake;
  Food food;
  Score score;
  MusicPlayer musicPlayer;
  Renderer renderer;
  SDL_Window *window;
  SDL_Renderer *gameRenderer;
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
