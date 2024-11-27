#include "Snake.h"

#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) : collidedWithBody(false), collidedWithWall(false), lives(5) {
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

void Snake::update() {
  handleMovements();
  checkForCollision();
}

void Snake::handleHeadBodyHit() {
  if (body.size() > 20) {
    for (int i = 10; i < body.size(); i++) {
      if (body[i].rect.x != body[0].rect.x && body[i].rect.y != body[0].rect.y) {
        if (SDL_HasIntersection(&body[i].rect, &body[0].rect)) {
          handleHit();
        }
      }
    }
  }
}

int Snake::getCurrentLives() { return lives; }

void Snake::checkForCollision() {
  if (collidedWithWall) {
    handleHit();
    collidedWithWall = false;
  }
  if (collidedWithBody) {
    handleHit();
    collidedWithBody = false;
  }
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
    if (i == 1) {
      SnakeSegment& prevSegment = body[0];
      switch (direction) {
        case LEFT:
          body[i].rect.x = prevSegment.rect.x + BASIC_UNITY_SIZE * 0.8;
          break;
        case RIGHT:
          body[i].rect.x = prevSegment.rect.x - BASIC_UNITY_SIZE * 0.8;
          break;
        case UP:
          body[i].rect.y = prevSegment.rect.y + BASIC_UNITY_SIZE * 0.8;
          break;
        case DOWN:
          body[i].rect.y = prevSegment.rect.y - BASIC_UNITY_SIZE * 0.8;

          break;
      }
      SDL_RenderCopyEx(renderer, spritesheetTexture, &bodySourceRect, &body[i].rect, 0, nullptr, SDL_FLIP_NONE);
    }
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
    if (body[0].rect.x == body[i].rect.x + body[i].rect.w && body[0].rect.y == body[i].rect.y) {
      std::cout << "collided with body from the left" << std::endl;
    }
  }

  SnakeSegment& headSegment = body[0];
  headSegment.rect.y += dy;

  if (headSegment.rect.y < 0) {
    headSegment.rect.y = 0;
    collidedWithWall = true;
  }
  if (headSegment.rect.y > WINDOW_HEIGHT - BASIC_UNITY_SIZE) {
    headSegment.rect.y = WINDOW_HEIGHT - BASIC_UNITY_SIZE;
    collidedWithWall = true;
  }
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

  if (headSegment.rect.x < 0) {
    headSegment.rect.x = 0;
    collidedWithWall = true;
  }
  if (headSegment.rect.x > WINDOW_WIDTH - BASIC_UNITY_SIZE) {
    headSegment.rect.x = WINDOW_WIDTH - BASIC_UNITY_SIZE;
    collidedWithWall = true;
  }
}

void Snake::handleMovements() {
  const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

  if (keyboardState[SDL_SCANCODE_UP]) {
    moveY(-SNAKE_SPEED);
  }
  if (keyboardState[SDL_SCANCODE_DOWN]) {
    moveY(SNAKE_SPEED);
  }
  if (keyboardState[SDL_SCANCODE_RIGHT]) {
    moveX(SNAKE_SPEED);
  }
  if (keyboardState[SDL_SCANCODE_LEFT]) {
    moveX(-SNAKE_SPEED);
  }
}

const std::vector<SnakeSegment>& Snake::getBody() const { return body; }

void Snake::increaseSize() {
  for (int i = 0; i < 3; i++) {
    const SnakeSegment& tailSegment = body.back();
    SDL_Rect newSegmentRect = {tailSegment.rect.x, tailSegment.rect.y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
    body.push_back({newSegmentRect, 0});
  }
}

void Snake::handleHit() { lives--; }
