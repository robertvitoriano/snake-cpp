#include "Snake.h"
#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) : x(xPos), y(yPos) {
  rect = {x, y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
}

void Snake::moveY(int dy) {
  y += dy;
  if (y < 0)
    y = 0;
  if (y > WINDOW_HEIGHT - BASIC_UNITY_SIZE)
    y = WINDOW_HEIGHT - BASIC_UNITY_SIZE;
  rect.y = y;
}
void Snake::moveX(int dx) {
  x += dx;
  if (x < 0)
    x = 0;
  if (x > WINDOW_WIDTH - BASIC_UNITY_SIZE)
    x = WINDOW_WIDTH - BASIC_UNITY_SIZE;
  rect.x = x;
}

const SDL_Rect &Snake::getRect() {
  rect.x = x;
  rect.y = y;
  return rect;
}
