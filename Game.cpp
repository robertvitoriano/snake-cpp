#include "Game.h"
#include "GameConstants.h"
#include <iostream>

Game::Game()
    : playerPaddle(20, WINDOW_HEIGHT / 2 - SNAKE_HEIGHT / 2),
      aiPaddle(WINDOW_WIDTH - 40, WINDOW_HEIGHT / 2 - SNAKE_HEIGHT / 2),
      running(true) {
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
    processInput();
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
    playerPaddle.move(-SNAKE_SPEED);
  }
  if (keyboardState[SDL_SCANCODE_DOWN]) {
    playerPaddle.move(SNAKE_SPEED);
  }
}

void Game::update() {
  ball.move();

  if (checkCollision(ball.getRect(), playerPaddle.getRect()) ||
      checkCollision(ball.getRect(), aiPaddle.getRect())) {
    ball.reverseX();
  }

  if (ball.isOutOfBounds()) {
    ball.reset();
  }

  if (ball.getRect().y < aiPaddle.getRect().y) {
    aiPaddle.move(-SNAKE_SPEED / 2);
  } else if (ball.getRect().y > aiPaddle.getRect().y + SNAKE_HEIGHT) {
    aiPaddle.move(SNAKE_SPEED / 2);
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &playerPaddle.getRect());
  SDL_RenderFillRect(renderer, &aiPaddle.getRect());
  SDL_RenderFillRect(renderer, &ball.getRect());

  SDL_RenderPresent(renderer);
}

bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b) {
  return SDL_HasIntersection(&a, &b);
}
