#ifndef FOOD_H
#define FOOD_H
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>

class Food {
public:
  Food();
  void reset();
  const SDL_Rect &getRect();
  bool isOutOfBounds() const;

private:
  int x, y;
  SDL_Rect rect;
};

#endif
