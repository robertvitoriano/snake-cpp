#include "Snake.h"

#include "GameConstants.h"

Snake::Snake(int xPos, int yPos)
    : collidedWithBody(false),
      collidedWithWall(false),
      lives(5),
      hitTimer(0),
      hitInterval(2000),
      isBlinking(false),
      blinkStartTime(0),
      blinkDuration(2000),
      blinkInterval(200),
      direction(RIGHT),
      bodySourceRect({64, 32, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE}),
      cornerSourceRect({64, 32, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE}),
      headSourceRect({32, 32, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE}),
      body{{{xPos, yPos, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE}, 0}},
      speed(0),
      isMovingDown(false),
      isMovingUp(false),
      isMovingLeft(false),
      isMovingRight(false) {
  this->direction = RIGHT;
  this->speed = SNAKE_INITIAL_SPEED;
}

void Snake::render(SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  if (this->isBlinking) {
    this->renderBlinkingSnake(renderer, spritesheetTexture);
  } else {
    this->renderSnakeHead(renderer, spritesheetTexture);
    this->renderSnakeBody(renderer, spritesheetTexture);
  }
}

void Snake::update() {
  this->handleMovements();
  this->checkForCollision();
  this->handleHeadBodyHit();
}

void Snake::handleHeadBodyHit() {
  if (this->body.size() > 20) {
    for (int i = 10; i < body.size(); i++) {
      if (SDL_HasIntersection(&body[i].rect, &body[0].rect)) {
        this->handleHit();
      }
    }
  }
}

int Snake::getCurrentLives() { return lives; }

void Snake::checkForCollision() {
  if (this->collidedWithWall) {
    this->handleHit();
    this->collidedWithWall = false;
  }
  if (this->collidedWithBody) {
    this->handleHit();
    this->collidedWithBody = false;
  }
}

void Snake::renderSnakeHead(SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  SnakeSegment& headSegment = this->body[0];

  switch (this->direction) {
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
  for (size_t i = 1; i < this->body.size(); ++i) {
    if (i == 1) {
      SnakeSegment& prevSegment = this->body[0];
      switch (direction) {
        case LEFT:
          this->body[i].rect.x = prevSegment.rect.x + BASIC_UNITY_SIZE;
          break;
        case RIGHT:
          this->body[i].rect.x = prevSegment.rect.x - BASIC_UNITY_SIZE;
          break;
        case UP:
          this->body[i].rect.y = prevSegment.rect.y + BASIC_UNITY_SIZE;
          break;
        case DOWN:
          this->body[i].rect.y = prevSegment.rect.y - BASIC_UNITY_SIZE;

          break;
      }
    }
    SDL_RenderCopyEx(renderer, spritesheetTexture, &bodySourceRect, &body[i].rect, 0, nullptr, SDL_FLIP_NONE);
  }
}

void Snake::renderBlinkingSnake(SDL_Renderer* renderer, SDL_Texture* spritesheetTexture) {
  Uint32 currentTime = SDL_GetTicks();
  if ((currentTime - this->blinkStartTime) / this->blinkInterval % 2 == 0) {
    renderSnakeHead(renderer, spritesheetTexture);
    renderSnakeBody(renderer, spritesheetTexture);
  } else {
    SDL_SetTextureColorMod(spritesheetTexture, 255, 0, 0);
    renderSnakeHead(renderer, spritesheetTexture);
    renderSnakeBody(renderer, spritesheetTexture);
    SDL_SetTextureColorMod(spritesheetTexture, 255, 255, 255);
  }

  if (currentTime > blinkStartTime + blinkDuration) {
    this->isBlinking = false;
  }
}

void Snake::moveY(int dy) {
  Direction lastDirection = this->direction;

  if (dy > 0)
    this->direction = DOWN;
  else if (dy < 0)
    this->direction = UP;

  for (size_t i = this->body.size() - 1; i > 0; --i) {
    this->body[i].rect = this->body[i - 1].rect;
  }

  SnakeSegment& headSegment = this->body[0];
  if ((lastDirection == UP && this->direction == DOWN || lastDirection == DOWN && this->direction == UP) &&
      this->collidedWithWall == false) {
    headSegment.rect.x += BASIC_UNITY_SIZE;
  }
  headSegment.rect.y += dy;

  if (headSegment.rect.y < 0) {
    headSegment.rect.y = 0;
    this->collidedWithWall = true;
  }
  if (headSegment.rect.y > WINDOW_HEIGHT - BASIC_UNITY_SIZE) {
    headSegment.rect.y = WINDOW_HEIGHT - BASIC_UNITY_SIZE;
    this->collidedWithWall = true;
  }
}

void Snake::moveX(int dx) {
  Direction lastDirection = this->direction;
  if (dx > 0) {
    this->direction = RIGHT;
  }

  else if (dx < 0)
    this->direction = LEFT;

  for (size_t i = this->body.size() - 1; i > 0; --i) {
    this->body[i].rect = this->body[i - 1].rect;
  }

  SnakeSegment& headSegment = body[0];
  if ((lastDirection == LEFT && this->direction == RIGHT || lastDirection == RIGHT && this->direction == LEFT) &&
      this->collidedWithWall == false) {
    headSegment.rect.y += BASIC_UNITY_SIZE;
  }
  headSegment.rect.x += dx;

  if (headSegment.rect.x < 0) {
    headSegment.rect.x = 0;
    this->collidedWithWall = true;
  }
  if (headSegment.rect.x > WINDOW_WIDTH - BASIC_UNITY_SIZE) {
    headSegment.rect.x = WINDOW_WIDTH - BASIC_UNITY_SIZE;
    this->collidedWithWall = true;
  }
}

void Snake::handleMovements() {
  const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);

  if (keyboardState[SDL_SCANCODE_UP]) {
    this->toggleMovingUp();
  }
  if (keyboardState[SDL_SCANCODE_DOWN]) {
    this->toggleMovingDown();
  }
  if (keyboardState[SDL_SCANCODE_RIGHT]) {
    this->toggleMovingRight();
  }
  if (keyboardState[SDL_SCANCODE_LEFT]) {
    this->toggleMovingLeft();
  }
  this->move();
}

const std::vector<SnakeSegment>& Snake::getBody() const { return body; }

void Snake::increaseSize() {
  MusicPlayer& musicPlayer = MusicPlayer::getInstance();
  musicPlayer.playSound("assets/sounds/sx/eat.wav", 0);

  for (int i = 0; i < 3; i++) {
    const SnakeSegment& tailSegment = body.back();
    SDL_Rect newSegmentRect = {tailSegment.rect.x, tailSegment.rect.y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
    body.push_back({newSegmentRect, 0});
  }
  if (this->speed % 2 != 0) this->speed++;
}

void Snake::handleHit() {
  if (SDL_GetTicks() > this->hitTimer + this->hitInterval) {
    this->lives--;
    this->hitTimer = SDL_GetTicks();

    MusicPlayer& musicPlayer = MusicPlayer::getInstance();
    musicPlayer.playSound("assets/sounds/sx/hit.wav", 0);

    this->isBlinking = true;
    this->blinkStartTime = SDL_GetTicks();
  }
}

void Snake::resetLives() { this->lives = 5; }

void Snake::increaseHealth() { this->lives++; }

void Snake::resetBody() {
  if (body.size() > 2) {
    body.erase(body.begin() + 1, body.end());
  }
}

void Snake::resetSpeed() { this->speed = SNAKE_INITIAL_SPEED; }

void Snake::reset() {
  this->resetBody();
  this->resetLives();
  this->resetSpeed();
}
void Snake::move() {
  if (this->isMovingUp) {
    this->moveY(-this->speed);
  } else if (this->isMovingDown) {
    this->moveY(this->speed);
  } else if (this->isMovingRight) {
    this->moveX(this->speed);
  } else if (this->isMovingLeft) {
    this->moveX(-this->speed);
  }
}
void Snake::toggleMovingUp() {
  this->isMovingUp = true;
  this->isMovingDown = false;
  this->isMovingLeft = false;
  this->isMovingRight = false;
}
void Snake::toggleMovingDown() {
  this->isMovingDown = true;
  this->isMovingUp = false;
  this->isMovingLeft = false;
  this->isMovingUp = false;
}
void Snake::toggleMovingRight() {
  this->isMovingRight = true;
  this->isMovingUp = false;
  this->isMovingDown = false;
  this->isMovingLeft = false;
}
void Snake::toggleMovingLeft() {
  this->isMovingLeft = true;
  this->isMovingRight = false;
  this->isMovingUp = false;
  this->isMovingDown = false;
}
