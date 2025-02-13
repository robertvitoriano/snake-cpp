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
      durationCounter(0),
      scoreGoal(0),
      currentLevelIndex(0),
      shouldSetLevelData(true) {
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

  try {
    inputFile >> this->levelsData;
    this->setLevelData();
  } catch (const nlohmann::json::parse_error &e) {
    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
  }
  inputFile.close();
}

Game::~Game() {
  SDL_DestroyTexture(spritesheetTexture);
  SDL_DestroyTexture(backgroundTexture);

  graphics.destroyRenderer();
}

void Game::setLevelData() {
  if (this->shouldSetLevelData) {
    this->levelName = this->levelsData[currentLevelIndex]["name"];
    this->backingTrack = this->levelsData[currentLevelIndex]["backingTrack"];
    this->background = this->levelsData[currentLevelIndex]["background"];
    this->duration = this->levelsData[currentLevelIndex]["duration"];
    this->scoreGoal = this->levelsData[currentLevelIndex]["score-goal"];

    this->powerUps.clear();

    for (const auto &powerUpRaw : this->levelsData[currentLevelIndex]["powerUps"]) {
      for (int i = 0; i <= powerUpRaw["quantity"]; i++) {
        this->powerUps.push_back(PowerUp(powerUpRaw["image"], powerUpRaw["type"]));
        bool textureAlreadyStored =
            this->powerUpTexturesMap.find(powerUpRaw["image"]) != this->powerUpTexturesMap.end();
        if (!textureAlreadyStored) {
          this->powerUpTexturesMap[powerUpRaw["image"]] = this->graphics.createTexture(powerUpRaw["image"]);
        }
      }
    }
    ui.setScoreGoal(this->scoreGoal);

    backgroundTexture = graphics.createTexture(this->background);
    MusicPlayer &musicPlayer = MusicPlayer::getInstance();
    musicPlayer.playMusic(this->backingTrack, -1);
    this->durationCounter = this->duration;
    this->shouldSetLevelData = false;
    this->snake.resetLives();
  }
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
  this->setLevelData();
  handleFoodEating();
  processInput();
  snake.update();
  ui.setLives(snake.getCurrentLives());
  this->updateTimer();
}
void Game::render() {
  SDL_RenderClear(gameRenderer);

  bool hasPlayerLost = snake.getCurrentLives() <= 0 || this->durationCounter <= 0;

  bool hasPlayerWon = this->scoreGoal == ui.getCurrentScore();

  if (!hasPlayerLost && !hasPlayerWon) {
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

    for (PowerUp &powerUp : this->powerUps) {
      powerUp.render(this->gameRenderer, this->powerUpTexturesMap[powerUp.getImageSrc()]);
    }

  } else if (hasPlayerWon) {
    this->loadNextLevel();
  } else if (hasPlayerLost) {
    SDL_Color textColor = {255, 255, 255};
    Position gameOverTextPosition = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    graphics.drawText("Game over!", textColor, gameOverTextPosition, gameRenderer);
    SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 2555);
  }
  SDL_RenderPresent(gameRenderer);
}

void Game::loadNextLevel() {
  this->currentLevelIndex++;
  ui.resetScore();
  this->shouldSetLevelData = true;
}

void Game::updateTimer() {
  if (SDL_GetTicks() >= this->timer && this->durationCounter > 0) {
    this->timer = SDL_GetTicks() + 1000;
    this->durationCounter--;
  } else if (this->timer > this->duration) {
  }
}

void Game::renderTimer() {
  SDL_Color durationTextColor = {255, 255, 255};
  Position durationTextPosition = {WINDOW_WIDTH / 2, 50};
  graphics.drawText(std::to_string(this->durationCounter), durationTextColor, durationTextPosition, gameRenderer);
}
bool Game::checkCollision(const SDL_Rect &a, const SDL_Rect &b) { return SDL_HasIntersection(&a, &b); }
