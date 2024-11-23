#include "Snake.h"

#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) {
  bodySourceRect = {64, 32, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  cornerSourceRect = {64, 32, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  headSourceRect = {32, 32, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

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

  SDL_RenderCopyEx(renderer, spritesheetTexture, &headSourceRect, &headSegment.rect, headSegment.angle, nullptr,
                   SDL_FLIP_NONE);
}

void Snake::renderSnakeBody(SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  for (size_t i = 1; i < body.size(); ++i) {
    SDL_RenderCopyEx(renderer, spritesheetTexture, &bodySourceRect, &body[i].rect, 0, nullptr, SDL_FLIP_NONE);
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
  body.push_back({newSegmentRect, 0});
}
