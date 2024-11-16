#include "Snake.h"
#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) {

  SDL_Rect head = {xPos, yPos, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

  xDirection = RIGHT;

  dx = 0, dy = 0;

  body.push_back(head);
}

void Snake::render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture) {
  if (body.empty()) {
    std::cerr << "Body is empty!" << std::endl;
    return;
  }

  const SDL_Rect snakeHeadSrcRect = {32, 32, BASIC_UNITY_SIZE,
                                     BASIC_UNITY_SIZE};
  const SDL_Rect bodySrcRect = {32, 0, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

  double angle = calculateAngle();

  SDL_RenderCopyEx(renderer, spritesheetTexture, &snakeHeadSrcRect, &body[0],
                   angle, nullptr, SDL_FLIP_NONE);

  for (size_t i = 1; i < body.size(); ++i) {
    SDL_RenderCopy(renderer, spritesheetTexture, &bodySrcRect, &body[i]);
  }
}
double Snake::calculateAngle() {
  if (dx + body[0].x != body[0].x) {
    dx = 0;
    if (xDirection == LEFT)
      return -90.0;
    if (xDirection == RIGHT)
      return 90;
  }

  if (dy + body[0].y != body[0].y) {
    dy = 0;

    if (yDirection == DOWN) {
      return 180;
    }
    if (yDirection == UP) {
      return -180.0;
    }
  }

  return 90.0;
}

void Snake::moveY(int speed) {

  dy = speed;

  if (dy > 0) {
    yDirection = DOWN;
  } else if (dy < 0) {
    yDirection = UP;
  }

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
  }
}
void Snake::moveX(int speed) {

  dx = speed;

  if (dx > 0)
    xDirection = RIGHT;
  else if (dx < 0)
    xDirection = LEFT;

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
  }
}
const std::vector<SDL_Rect> &Snake::getBody() const { return body; }

void Snake::increaseSize() {
  std::cout << "collision, should inscrease" << std::endl;
  if (xDirection == RIGHT) {
    body.push_back(
        {(int)body[body.size() - 1].x - BASIC_UNITY_SIZE * (int)body.size(),
         (int)body[0].y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE});
  }
  if (xDirection == LEFT) {
    body.push_back(
        {(int)body[body.size() - 1].x + BASIC_UNITY_SIZE * (int)body.size(),
         (int)body[0].y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE});
  }
}

void Snake::updateBodyPositions() {}
