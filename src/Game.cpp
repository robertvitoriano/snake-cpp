#include "Game.h"

#include "GameConstants.h"

Game::Game() : snake(20, WINDOW_HEIGHT / 2 - BASIC_UNITY_SIZE / 2), running(true), gameOver(false) {
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
  snake.update();
}
void Game::handleFoodEating() {
  std::vector<SnakeSegment> snakeBody = snake.getBody();

  for (const SnakeSegment &segment : snakeBody) {
    if (checkCollision(food.getRect(), segment.rect)) {
      snake.increaseSize();
      food.reset();
      score.updateScore();
    }
  }
}
void Game::update() {
  handleFoodEating();
  processInput();
  snake.update();
}
void Game::render() {
  SDL_RenderClear(gameRenderer);
  if (!gameOver) {
    SDL_Rect backgroundRectSrc = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Rect backgroundRectDest = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderCopy(gameRenderer, backgroundTexture, &backgroundRectSrc, &backgroundRectDest);

    snake.render(gameRenderer, spritesheetTexture);
    food.render(gameRenderer, spritesheetTexture);
    score.render(gameRenderer, spritesheetTexture);

  } else {
    SDL_Color textColor = {255, 255, 255};
    Position postion = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    renderer.drawText("Game over!", textColor, postion, gameRenderer);
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 2555);
  }
  SDL_RenderPresent(gameRenderer);
}

bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b) { return SDL_HasIntersection(&a, &b); }
