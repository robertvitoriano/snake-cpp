#include "Game.h"
#include "GameConstants.h"
#include <iostream>

Game::Game()
    : snake(20, WINDOW_HEIGHT / 2 - BASIC_UNITY_SIZE / 2), running(true) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
  }

  window = SDL_CreateWindow("Pong Game", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_SHOWN);
  if (!window) {
    SDL_Quit();
    throw std::runtime_error("SDL_CreateWindow Error: " +
                             std::string(SDL_GetError()));
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    throw std::runtime_error("SDL_CreateRenderer Error: " +
                             std::string(SDL_GetError()));
  }
}

Game::~Game() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
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

void Game::update() {

  if (checkCollision(food.getRect(), snake.getRect())) {
    std::cout << "Collision detected!" << std::endl;
  }

  processInput();
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &snake.getRect());

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderFillRect(renderer, &food.getRect());

  SDL_RenderPresent(renderer);
}

bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b) {

  return SDL_HasIntersection(&a, &b);
}
