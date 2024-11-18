#include "Snake.h"

#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) {
  bodySourceRect = {32, 0, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  SDL_Rect headRect = {xPos, yPos, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  body.push_back({headRect, 0});
  direction = RIGHT;
}

void Snake::render(SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  if (body.empty()) {
    std::cerr << "Body is empty!" << std::endl;
    return;
  }
  renderSnakeHead(renderer, spritesheetTexture);
  renderSnakeBody(renderer, spritesheetTexture);
}

void Snake::renderSnakeHead(SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  SDL_Rect snakeHeadSrcRect = {32, 32, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  SnakeSegment& headSegment = body[0];

  switch (direction) {
    case RIGHT:
      headSegment.angle = 90.0;
      break;
    case DOWN:
      headSegment.angle = 180.0;
      break;
    case LEFT:
      headSegment.angle = -90.0;
      break;
    case UP:
      headSegment.angle = 0.0;
      break;
  }

  SDL_RenderCopyEx(renderer, spritesheetTexture, &snakeHeadSrcRect, &headSegment.rect, headSegment.angle, nullptr,
                   SDL_FLIP_NONE);
}

void Snake::renderSnakeBody(SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  Direction prevDirection = direction;
  for (size_t i = 1; i < body.size(); ++i) {
    const SnakeSegment& prevSegment = body[i - 1];

    SnakeSegment& currentSegment = body[i];

    currentSegment.angle = prevSegment.angle;

    switch (prevDirection) {
      case LEFT:
        currentSegment.rect.x = prevSegment.rect.x + BASIC_UNITY_SIZE;
        break;
      case RIGHT:
        currentSegment.rect.x = prevSegment.rect.x - BASIC_UNITY_SIZE;
        break;
      case UP:

        currentSegment.rect.y = prevSegment.rect.y + BASIC_UNITY_SIZE;
        break;
      case DOWN:
        currentSegment.rect.y = prevSegment.rect.y - BASIC_UNITY_SIZE;
        break;
    }

    if (i == 1 && body[0].angle == 0 || body[0].angle == 180) {
      currentSegment.angle = 90;

    } else if (i == 1 && body[0].angle == 90 || body[0].angle == -90) {
      currentSegment.angle = 0;
    }

    SDL_RenderCopyEx(renderer, spritesheetTexture, &bodySourceRect, &currentSegment.rect, currentSegment.angle, nullptr,
                     SDL_FLIP_NONE);
  }
}

void Snake::moveY(int dy) {
  if (dy > 0)
    direction = DOWN;
  else if (dy < 0)
    direction = UP;

  for (size_t i = body.size() - 1; i > 0; --i) {
    body[i].rect = body[i - 1].rect;
  }

  SnakeSegment& headSegment = body[0];
  headSegment.rect.y += dy;

  if (headSegment.rect.y < 0) headSegment.rect.y = 0;
  if (headSegment.rect.y > WINDOW_HEIGHT - BASIC_UNITY_SIZE) headSegment.rect.y = WINDOW_HEIGHT - BASIC_UNITY_SIZE;
}

void Snake::moveX(int dx) {
  if (dx > 0)
    direction = RIGHT;
  else if (dx < 0)
    direction = LEFT;

  for (size_t i = body.size() - 1; i > 0; --i) {
    body[i].rect = body[i - 1].rect;
  }

  SnakeSegment& headSegment = body[0];
  headSegment.rect.x += dx;

  if (headSegment.rect.x < 0) headSegment.rect.x = 0;
  if (headSegment.rect.x > WINDOW_WIDTH - BASIC_UNITY_SIZE) headSegment.rect.x = WINDOW_WIDTH - BASIC_UNITY_SIZE;
}

const std::vector<SnakeSegment>& Snake::getBody() const { return body; }

void Snake::increaseSize() {
  const SnakeSegment& tailSegment = body.back();
  SDL_Rect newSegmentRect = {tailSegment.rect.x, tailSegment.rect.y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  body.push_back({newSegmentRect, 0.0});
}
