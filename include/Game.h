#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Food.h"
#include "Graphics.h"
#include "MusicPlayer.h"
#include "Snake.h"
#include "UI.h"

class Game {
 public:
  Game();
  ~Game();
  void run();

 private:
  int timer;
  int duration;
  int durationCounter;
  int scoreGoal;
  int currentLevelIndex;
  Snake snake;
  Food food;
  UI ui;
  Graphics graphics;
  SDL_Window *window;
  SDL_Renderer *gameRenderer;
  SDL_Texture *spritesheetTexture;
  SDL_Texture *heartTexture;
  SDL_Texture *backgroundTexture;
  nlohmann::json levelsData;

  std::string levelName;
  std::string backingTrack;
  std::string background;

  bool running;
  bool gameOver;
  bool shouldSetLevelData;
  void processInput();
  void handleFoodEating();
  void update();
  void render();
  bool checkCollision(const SDL_Rect &a, const SDL_Rect &b);
  void updateTimer();
  void renderTimer();
  void setLevelData();
};

#endif
