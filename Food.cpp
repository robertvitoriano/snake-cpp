#include "Food.h"
#include "GameConstants.h"

Food::Food() {
  std::srand(std::time(nullptr));
  reset();
}

void Food::reset() {
  x = (std::rand() % (WINDOW_WIDTH / BASIC_UNITY_SIZE)) * BASIC_UNITY_SIZE;
  y = (std::rand() % (WINDOW_HEIGHT / BASIC_UNITY_SIZE)) * BASIC_UNITY_SIZE;

  rect = {x, y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
}

const SDL_Rect &Food::getRect() {
  rect.x = x;
  rect.y = y;
  return rect;
}

bool Food::isOutOfBounds() const {
  return x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT;
}
