#include "Snake.h"

#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) : turnUpDelay(200), timeStartedToTurnUp(0), timeStartedToTurnDown(0) {
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

  renderSnakeBody(renderer, spritesheetTexture);
}

void Snake::renderSnakeBody(SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  Direction prevDirection = direction;
  for (size_t i = 1; i < body.size(); ++i) {
    const SnakeSegment& prevSegment = body[i - 1];
    SnakeSegment& currentSegment = body[i];

    SDL_Rect bodyDestinationRect = currentSegment.rect;
    double turnAngle = 0;
    switch (prevDirection) {
      case LEFT:
        bodyDestinationRect.x = prevSegment.rect.x + BASIC_UNITY_SIZE;
        break;
      case RIGHT:
        bodyDestinationRect.x = prevSegment.rect.x - BASIC_UNITY_SIZE;
        break;
      case UP:
        bodyDestinationRect.y = prevSegment.rect.y + BASIC_UNITY_SIZE;
        turnAngle = 90;
        break;
      case DOWN:
        bodyDestinationRect.y = prevSegment.rect.y - BASIC_UNITY_SIZE;
        turnAngle = 90;
        break;
    }

    if (direction == UP && (prevDirection == RIGHT || prevDirection == LEFT)) {
      handleBodyTurnUpAnimation(i, renderer, spritesheetTexture);
    } else {
      SDL_RenderCopyEx(renderer, spritesheetTexture, &bodySourceRect, &bodyDestinationRect, turnAngle, nullptr,
                       SDL_FLIP_NONE);
    }

    currentSegment.rect = bodyDestinationRect;
    prevDirection = direction;
  }
}

void Snake::handleBodyTurnUpAnimation(int snakeBodyIndex, SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  if (timeStartedToTurnUp == 0) {
    timeStartedToTurnUp = SDL_GetTicks();
  }

  bool shouldTurnUp = (SDL_GetTicks() - timeStartedToTurnUp) >= turnUpDelay;

  if (shouldTurnUp) {
    turnSnakeBodySegmentUp(snakeBodyIndex, renderer, spritesheetTexture);
    if (snakeBodyIndex == (body.size() - 1)) {
      timeStartedToTurnUp = 0;
    }
  }
}

void Snake::turnSnakeBodySegmentUp(int snakeBodyIndex, SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  const SnakeSegment& prevSegment = body[snakeBodyIndex - 1];
  SDL_Rect bodyDestinationRect = {prevSegment.rect.x, prevSegment.rect.y - BASIC_UNITY_SIZE, BASIC_UNITY_SIZE,
                                  BASIC_UNITY_SIZE};

  SDL_RenderCopyEx(renderer, spritesheetTexture, &bodySourceRect, &bodyDestinationRect, 90.0, nullptr, SDL_FLIP_NONE);

  body[snakeBodyIndex].rect = bodyDestinationRect;
  body[snakeBodyIndex].angle = 90.0;
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
