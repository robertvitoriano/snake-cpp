#include "Game.h"

#include "GameConstants.h"

Game::Game()
    : snake(20, WINDOW_HEIGHT / 2 - BASIC_UNITY_SIZE / 2),
      running(true),
      gameOver(false),
      levelName(""),
      backingTrack(""),
      background(""),
      timer(0),
      duration(0),
      durationCounter(0) {
  gameRenderer = graphics.createRenderer("Snake Game");
  spritesheetTexture = graphics.createTexture("assets/images/spritesheet.png");
  heartTexture = graphics.createTexture("assets/images/heart.png");

  if (!spritesheetTexture) {
    graphics.destroyRenderer();
    throw std::runtime_error("Failed to load spritesheet texture");
  }

  std::string filePath = "levels.json";
  std::ifstream inputFile(filePath);

  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open file " << filePath << std::endl;
  }

  nlohmann::json levelsData;

  try {
    inputFile >> levelsData;

    this->levelName = levelsData["name"];
    this->backingTrack = levelsData["backingTrack"];
    this->background = levelsData["background"];
    this->duration = levelsData["duration"];
  } catch (const nlohmann::json::parse_error &e) {
    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
  }
  inputFile.close();

  backgroundTexture = graphics.createTexture(this->background);
  MusicPlayer &musicPlayer = MusicPlayer::getInstance();
  musicPlayer.playMusic(this->backingTrack, -1);
}

Game::~Game() {
  SDL_DestroyTexture(spritesheetTexture);
  SDL_DestroyTexture(backgroundTexture);

  graphics.destroyRenderer();
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
      ui.updateScore();
    }
  }
}
void Game::update() {
  handleFoodEating();
  processInput();
  snake.update();
  ui.setLives(snake.getCurrentLives());
  this->updateTimer();
}
void Game::render() {
  SDL_RenderClear(gameRenderer);
  if (snake.getCurrentLives() > 0) {
    SDL_Rect backgroundRectSrc = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Rect backgroundRectDest = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderCopy(gameRenderer, backgroundTexture, &backgroundRectSrc, &backgroundRectDest);

    snake.render(gameRenderer, spritesheetTexture);
    food.render(gameRenderer, spritesheetTexture);
    ui.render(gameRenderer, spritesheetTexture, heartTexture);
    this->renderTimer();

    SDL_Color textColor = {255, 255, 255};
    Position titlePosition = {WINDOW_WIDTH / 2, 100};

    if (this->levelName.size() > 0) {
      graphics.drawText(this->levelName, textColor, titlePosition, gameRenderer);
    }

  } else if (snake.getCurrentLives() == 0 || this->timer == this->duration) {
    SDL_Color textColor = {255, 255, 255};
    Position gameOverTextPosition = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    graphics.drawText("Game over!", textColor, gameOverTextPosition, gameRenderer);
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 2555);
  }
  SDL_RenderPresent(gameRenderer);
}
void Game::updateTimer() {
  if (SDL_GetTicks() >= this->timer && this->durationCounter < this->duration) {
    this->timer = SDL_GetTicks() + 1000;
    this->durationCounter++;
  } else if (this->timer > this->duration) {
  }
}

void Game::renderTimer() {
  SDL_Color durationTextColor = {255, 255, 255};
  Position durationTextPosition = {WINDOW_WIDTH / 2, 50};
  graphics.drawText(std::to_string(this->durationCounter), durationTextColor, durationTextPosition, gameRenderer);
}
bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b) { return SDL_HasIntersection(&a, &b); }
