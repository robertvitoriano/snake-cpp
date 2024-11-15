#include "Snake.h"
#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) : x(xPos), y(yPos) {

  SDL_Rect head = {x, y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  body.push_back(head);
}

void Snake::moveY(int dy) {
  y += dy;
  if (y < 0)
    y = 0;
  if (y > WINDOW_HEIGHT - BASIC_UNITY_SIZE)
    y = WINDOW_HEIGHT - BASIC_UNITY_SIZE;
  body[0].y = y;
}
void Snake::moveX(int dx) {
  x += dx;
  if (x < 0)
    x = 0;
  if (x > WINDOW_WIDTH - BASIC_UNITY_SIZE)
    x = WINDOW_WIDTH - BASIC_UNITY_SIZE;
  body[0].x = x;
}
const std::vector<SDL_Rect> &Snake::getBody() const { return body; }

void Snake::handleFoodEating() {
  body.push_back({x, y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE});
}

void Snake::updateBodyPositions() {}
