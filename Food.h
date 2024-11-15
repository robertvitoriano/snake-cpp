#ifndef FOOD_H
#define FOOD_H

#include <SDL2/SDL.h>

class Food {
public:
  Food();
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
