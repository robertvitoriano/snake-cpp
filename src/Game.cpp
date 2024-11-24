#include "Game.h"

#include "GameConstants.h"

Game::Game() : snake(20, WINDOW_HEIGHT / 2 - BASIC_UNITY_SIZE / 2), running(true) {
  gameRenderer = renderer.createRenderer("Snake Game");
  spritesheetTexture = renderer.createTexture("assets/images/spritesheet.png");

  if (!spritesheetTexture) {
    renderer.destroyRenderer();
    throw std::runtime_error("Failed to load spritesheet texture");
  }

  backgroundTexture = renderer.createTexture("assets/images/background.png");

  musicPlayer.play("assets/sounds/background.mp3");
}

Game::~Game() {
  SDL_DestroyTexture(spritesheetTexture);
  SDL_DestroyTexture(backgroundTexture);

  renderer.destroyRenderer();
}

void Game::run() {
  while (running) {
    update();
    render();
  }
}

void Game::processInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      running = false;
    }
  }

  const Uint8 *keyboardState = SDL_GetKeyboardState(nullptr);

  if (keyboardState[SDL_SCANCODE_UP]) {
    snake.moveY(-SNAKE_SPEED);
  }
  if (keyboardState[SDL_SCANCODE_DOWN]) {
    snake.moveY(SNAKE_SPEED);
  }
  if (keyboardState[SDL_SCANCODE_RIGHT]) {
    snake.moveX(SNAKE_SPEED);
  }
  if (keyboardState[SDL_SCANCODE_LEFT]) {
    snake.moveX(-SNAKE_SPEED);
  }
}
void Game::handleFoodEating() {
  std::vector<SnakeSegment> snakeBody = snake.getBody();

  for (const SnakeSegment &segment : snakeBody) {
    if (checkCollision(food.getRect(), segment.rect)) {
      snake.increaseSize();
      food.reset();
      score.updateScore();
      backgroundTexture = renderer.createTexture("assets/images/background-2.png");
    }
  }
}
void Game::update() {
  handleFoodEating();
  processInput();
}
void Game::render() {
  SDL_RenderClear(gameRenderer);

  SDL_Rect backgroundRectSrc = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_Rect backgroundRectDest = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

  SDL_RenderCopy(gameRenderer, backgroundTexture, &backgroundRectSrc, &backgroundRectDest);

  snake.render(gameRenderer, spritesheetTexture);
  food.render(gameRenderer, spritesheetTexture);
  score.render(gameRenderer, spritesheetTexture);

  SDL_RenderPresent(gameRenderer);
}

bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b) { return SDL_HasIntersection(&a, &b); }
