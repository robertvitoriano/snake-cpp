#include "Game.h"
#include "GameConstants.h"

Game::Game()
    : snake(20, WINDOW_HEIGHT / 2 - BASIC_UNITY_SIZE / 2), running(true) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    SDL_Quit();
    throw std::runtime_error("IMG_Init Error: " + std::string(IMG_GetError()));
  }

  window = SDL_CreateWindow("Snake Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_SHOWN);
  if (!window) {
    IMG_Quit();
    SDL_Quit();
    throw std::runtime_error("SDL_CreateWindow Error: " +
                             std::string(SDL_GetError()));
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer) {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    throw std::runtime_error("SDL_CreateRenderer Error: " +
                             std::string(SDL_GetError()));
  }

  SDL_Surface *surface = IMG_Load("assets/spritesheet.png");

  if (!surface) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    throw std::runtime_error("IMG_Load Error: " + std::string(IMG_GetError()));
  }
  spritesheetTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!spritesheetTexture) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    throw std::runtime_error("SDL_CreateTextureFromSurface Error: " +
                             std::string(SDL_GetError()));
  }
}

Game::~Game() {
  SDL_DestroyTexture(spritesheetTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
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
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  snake.render(renderer, spritesheetTexture);
  food.render(renderer, spritesheetTexture);

  SDL_RenderPresent(renderer);
}

bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b) {

  return SDL_HasIntersection(&a, &b);
}
