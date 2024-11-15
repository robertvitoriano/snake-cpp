#include "Game.h"
#include "GameConstants.h"

Game::Game()
    : snake(20, WINDOW_HEIGHT / 2 - BASIC_UNITY_SIZE / 2), running(true) {

  gameRenderer = renderer.createRenderer("Snake Game");
  spritesheetTexture = renderer.createTexture("assets/spritesheet.png");

  if (!spritesheetTexture) {
    renderer.destroyRenderer();
    throw std::runtime_error("Failed to load spritesheet texture");
  }
}

Game::~Game() {
  SDL_DestroyTexture(spritesheetTexture);
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
  std::vector<SDL_Rect> snakeBody = snake.getBody();

  for (const SDL_Rect &segment : snakeBody) {
    if (checkCollision(food.getRect(), segment)) {
      snake.increaseSize();
      food.reset();
    }
  }
}
void Game::update() {
  handleFoodEating();
  processInput();
}
void Game::render() {
  SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
  SDL_RenderClear(gameRenderer);

  snake.render(gameRenderer, spritesheetTexture);
  food.render(gameRenderer, spritesheetTexture);

  SDL_RenderPresent(gameRenderer);
}

bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b) {

  return SDL_HasIntersection(&a, &b);
}
