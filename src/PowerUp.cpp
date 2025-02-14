#include <PowerUp.hpp>

PowerUp::PowerUp(std::string imageSrc, PowerUpType type, int timeToShow)
    : _position({0, 0}), _size({BASIC_UNITY_SIZE, BASIC_UNITY_SIZE}) {
  static bool seedInitialized = false;

  if (!seedInitialized) {
    srand(static_cast<unsigned>(time(nullptr)));
    seedInitialized = true;
  }

  this->_position.x = rand() % (WINDOW_WIDTH - BASIC_UNITY_SIZE);
  this->_imageSrc = imageSrc;
  this->_type = type;
  this->_timeToShow = timeToShow;
}

void PowerUp::update() {
  this->_position.y += 4;
  this->_powerUpRect = {this->_position.x, this->_position.y, this->_size.width, this->_size.height};
}

void PowerUp::onHit() {}

void PowerUp::render(SDL_Renderer *renderer, SDL_Texture *powerUpTexture) {
  SDL_Rect powerUpSourceRect = {0, 0, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

  SDL_RenderCopy(renderer, powerUpTexture, &powerUpSourceRect, &this->_powerUpRect);
}

std::string PowerUp::getImageSrc() { return this->_imageSrc; }

PowerUpType PowerUp::getType() { return this->_type; }

int PowerUp::getTimeToShow() { return this->_timeToShow; }
bool PowerUp::isOutOfScreen() { return this->_position.y > WINDOW_HEIGHT; }
const SDL_Rect &PowerUp::getRect() { return this->_powerUpRect; }
