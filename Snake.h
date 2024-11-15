#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <vector>

class Snake {
public:
  Snake(int xPos, int yPos);
  void moveY(int dy);
  void moveX(int dx);
  void handleFoodEating();
  const std::vector<SDL_Rect> &getBody() const;

private:
  int x, y;
  std::vector<SDL_Rect> body;
  void updateBodyPositions();
};

#endif
