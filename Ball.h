#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>

class Ball {
public:
  Ball();
  void move();
  void reset();
  const SDL_Rect &getRect();
  void reverseX();
  bool isOutOfBounds() const;

private:
  int x, y, vx, vy;
  SDL_Rect rect;
};

#endif
