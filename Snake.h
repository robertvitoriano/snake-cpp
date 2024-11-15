#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>

class Snake {
public:
  Snake(int xPos, int yPos);
  void moveY(int dy);
  void moveX(int dx);

  const SDL_Rect &getRect();

private:
  int x, y;
  SDL_Rect rect;
};

#endif
