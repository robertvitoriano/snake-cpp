#include "Paddle.h"
#include "GameConstants.h"

Paddle::Paddle(int xPos, int yPos) : x(xPos), y(yPos) {
  rect = {x, y, PADDLE_WIDTH, PADDLE_HEIGHT};
}

void Paddle::move(int dy) {
  y += dy;
  if (y < 0)
    y = 0;
  if (y > WINDOW_HEIGHT - PADDLE_HEIGHT)
    y = WINDOW_HEIGHT - PADDLE_HEIGHT;
  rect.y = y;
}

const SDL_Rect &Paddle::getRect() {
  rect.x = x;
  rect.y = y;
  return rect;
}
