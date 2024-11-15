#include "Ball.h"
#include "GameConstants.h"

Ball::Ball() { reset(); }

void Ball::move() {
  x += vx;
  y += vy;
  if (y <= 0 || y >= WINDOW_HEIGHT - BALL_SIZE) {
    vy = -vy;
  }
  rect.x = x;
  rect.y = y;
}

void Ball::reset() {
  x = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
  y = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;
  vx = BALL_SPEED;
  vy = BALL_SPEED;
  rect = {x, y, BALL_SIZE, BALL_SIZE};
}

const SDL_Rect &Ball::getRect() {
  rect.x = x;
  rect.y = y;
  return rect;
}

void Ball::reverseX() { vx = -vx; }

bool Ball::isOutOfBounds() const { return x < 0 || x > WINDOW_WIDTH; }
