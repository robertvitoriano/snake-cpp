#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>

class Snake {
public:
  Snake(int xPos, int yPos);
  void move(int dy);
  const SDL_Rect &getRect();

private:
  int x, y;
  SDL_Rect rect;
};

#endif
