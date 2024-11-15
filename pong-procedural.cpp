#include <SDL2/SDL.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;
const int BALL_SIZE = 20;
const int PADDLE_SPEED = 10;
const int BALL_SPEED = 5;

struct Paddle {
  int x, y;
};

struct Ball {
  int x, y, vx, vy;
};

void movePaddle(Paddle &paddle, int dy) {
  paddle.y += dy;
  if (paddle.y < 0)
    paddle.y = 0;
  if (paddle.y > WINDOW_HEIGHT - PADDLE_HEIGHT)
    paddle.y = WINDOW_HEIGHT - PADDLE_HEIGHT;
}

void resetBall(Ball &ball) {
  ball.x = WINDOW_WIDTH / 2 - BALL_SIZE / 2;
  ball.y = WINDOW_HEIGHT / 2 - BALL_SIZE / 2;
  ball.vx = BALL_SPEED;
  ball.vy = BALL_SPEED;
}

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Pong Game", 100, 100, WINDOW_WIDTH,
                                        WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    SDL_DestroyWindow(window);
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  Paddle playerPaddle = {20, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2};
  Paddle aiPaddle = {WINDOW_WIDTH - 40, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2};
  Ball ball;
  resetBall(ball);

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_UP]) {
      movePaddle(playerPaddle, -PADDLE_SPEED);
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
      movePaddle(playerPaddle, PADDLE_SPEED);
    }

    ball.x += ball.vx;
    ball.y += ball.vy;

    if (ball.y <= 0 || ball.y >= WINDOW_HEIGHT - BALL_SIZE) {
      ball.vy = -ball.vy;
    }

    if ((ball.x <= playerPaddle.x + PADDLE_WIDTH &&
         ball.y + BALL_SIZE > playerPaddle.y &&
         ball.y < playerPaddle.y + PADDLE_HEIGHT) ||
        (ball.x + BALL_SIZE >= aiPaddle.x && ball.y + BALL_SIZE > aiPaddle.y &&
         ball.y < aiPaddle.y + PADDLE_HEIGHT)) {
      ball.vx = -ball.vx;
    }

    if (ball.x < 0 || ball.x > WINDOW_WIDTH) {
      resetBall(ball);
    }

    if (ball.y < aiPaddle.y) {
      movePaddle(aiPaddle, -PADDLE_SPEED / 2);
    } else if (ball.y > aiPaddle.y + PADDLE_HEIGHT) {
      movePaddle(aiPaddle, PADDLE_SPEED / 2);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect playerRect = {playerPaddle.x, playerPaddle.y, PADDLE_WIDTH,
                           PADDLE_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &playerRect);

    SDL_Rect aiRect = {aiPaddle.x, aiPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT};
    SDL_RenderFillRect(renderer, &aiRect);

    SDL_Rect ballRect = {ball.x, ball.y, BALL_SIZE, BALL_SIZE};
    SDL_RenderFillRect(renderer, &ballRect);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
