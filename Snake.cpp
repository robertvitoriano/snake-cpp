#include "Snake.h"
#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) {

  SDL_Rect head = {xPos, yPos, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

  direction = RIGHT;
  body.push_back(head);
}

void Snake::render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture) {
  if (body.empty()) {
    std::cerr << "Body is empty!" << std::endl;
    return;
  }

  SDL_Rect snakeHeadSrcRect = {32, 32, 32, 32};
  SDL_Rect bodySrcRect = {32, 0, 32, 32};

  double angle = 0.0;
  std::cout << "ANGLE: " << angle << std::endl;

  switch (direction) {
  case RIGHT:
    angle = 90.0;
    break;
  case DOWN:
    angle = 180.0;
    break;
  case LEFT:
    angle = -90;
    break;
  case UP:
    angle = 0;
    break;
  }
  std::cout << "DIRECTION:" << direction << std::endl;

  SDL_RenderCopyEx(renderer, spritesheetTexture, &snakeHeadSrcRect, &body[0],
                   angle, nullptr, SDL_FLIP_NONE);

  for (size_t i = 1; i < body.size(); ++i) {
    SDL_RenderCopy(renderer, spritesheetTexture, &bodySrcRect, &body[i]);
  }
}

void Snake::moveY(int dy) {

  if (dy > 0)
    direction = DOWN;
  else if (dy < 0)
    direction = UP;

  for (size_t index = 0; index < body.size(); ++index) {

    SDL_Rect &segment = body[index];
    if (segment.y < 0) {
      segment.y = 0;
      continue;
    }
    if (segment.y > WINDOW_HEIGHT - BASIC_UNITY_SIZE) {
      segment.y = WINDOW_HEIGHT - BASIC_UNITY_SIZE;
      continue;
    }

    segment.y += dy;
    std::cout << "Index: " << index << ", Y: " << segment.y << "\n";
  }
}
void Snake::moveX(int dx) {

  if (dx > 0)
    direction = RIGHT;
  else if (dx < 0)
    direction = LEFT;

  for (size_t index = 0; index < body.size(); ++index) {

    SDL_Rect &segment = body[index];

    if (index == 0) {
      segment.x += dx;
      continue;
    }

    if (segment.x < 0) {
      segment.x = 0;
    }
    if (segment.x >= WINDOW_WIDTH - BASIC_UNITY_SIZE) {
      segment.x = WINDOW_WIDTH - BASIC_UNITY_SIZE;
    }
    if (dx > 0) {
      segment.x =
          body[index - 1].x - BASIC_UNITY_SIZE - SPACE_BETWEEN_BODY_PARTS;
    }
    if (dx < 0) {
      segment.x =
          body[index - 1].x + BASIC_UNITY_SIZE + SPACE_BETWEEN_BODY_PARTS;
    }

    segment.x += dx;

    std::cout << "Index: " << index << ", x: " << segment.x << "\n";
  }
}
const std::vector<SDL_Rect> &Snake::getBody() const { return body; }

void Snake::increaseSize() {
  if (direction == RIGHT) {
    body.push_back(
        {(int)body[body.size() - 1].x - BASIC_UNITY_SIZE * (int)body.size(),
         (int)body[0].y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE});
  }
  if (direction == LEFT) {
    body.push_back(
        {(int)body[body.size() - 1].x + BASIC_UNITY_SIZE * (int)body.size(),
         (int)body[0].y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE});
  }
}

void Snake::updateBodyPositions() {}
