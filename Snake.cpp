#include "Snake.h"
#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) : x(xPos), y(yPos) {
  rect = {x, y, SNAKE_WIDTH, SNAKE_HEIGHT};
}

void Snake::move(int dy) {
  y += dy;
  if (y < 0)
    y = 0;
  if (y > WINDOW_HEIGHT - SNAKE_HEIGHT)
    y = WINDOW_HEIGHT - SNAKE_HEIGHT;
  rect.y = y;
}

const SDL_Rect &Snake::getRect() {
  rect.x = x;
  rect.y = y;
  return rect;
}
