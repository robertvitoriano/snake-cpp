#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class Snake {
public:
  Snake(int xPos, int yPos);
  void moveY(int dy);
  void moveX(int dx);
  void handleFoodEating();
  const std::vector<SDL_Rect> &getBody() const;
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);

private:
  std::vector<SDL_Rect> body;
  void updateBodyPositions();
};

#endif
