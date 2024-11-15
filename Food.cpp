#include "Food.h"
#include "GameConstants.h"

Food::Food() { reset(); }

void Food::move() {
  x += vx;
  y += vy;
  if (y <= 0 || y >= WINDOW_HEIGHT - BASIC_UNITY_SIZE) {
    vy = -vy;
  }
  rect.x = x;
  rect.y = y;
}

void Food::reset() {
  x = WINDOW_WIDTH / 2 - BASIC_UNITY_SIZE / 2;
  y = WINDOW_HEIGHT / 2 - BASIC_UNITY_SIZE / 2;
  vx = FOOD_SPEED;
  vy = FOOD_SPEED;
  rect = {x, y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
}

const SDL_Rect &Food::getRect() {
  rect.x = x;
  rect.y = y;
  return rect;
}

void Food::reverseX() { vx = -vx; }

bool Food::isOutOfBounds() const { return x < 0 || x > WINDOW_WIDTH; }
