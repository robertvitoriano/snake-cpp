#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

class Paddle {
public:
  Paddle(int xPos, int yPos);
  void move(int dy);
  const SDL_Rect &getRect();

private:
  int x, y;
  SDL_Rect rect;
};

#endif
