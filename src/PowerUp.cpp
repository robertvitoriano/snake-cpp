#include <PowerUp.hpp>

PowerUp::PowerUp(std::string imageSrc, PowerUpType type)
    : _position({0, 0}), _size({BASIC_UNITY_SIZE, BASIC_UNITY_SIZE}) {
  static bool seedInitialized = false;

  if (!seedInitialized) {
    srand(static_cast<unsigned>(time(nullptr)));
    seedInitialized = true;
  }

  this->_position.x = rand() % (WINDOW_WIDTH - BASIC_UNITY_SIZE);
  this->_imageSrc = imageSrc;
  this->_type = type;
}

void PowerUp::update() { this->_position.y += 1; }

void PowerUp::onHit() {}

void PowerUp::render(SDL_Renderer *renderer, SDL_Texture *powerUpTexture) {
  SDL_Rect powerUpRect = {this->_position.x, this->_position.y, this->_size.width, this->_size.height};
  SDL_Rect powerUpSourceRect = {0, 0, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

  SDL_RenderCopy(renderer, powerUpTexture, &powerUpSourceRect, &powerUpRect);
}

std::string PowerUp::getImageSrc() { return this->_imageSrc; }

PowerUpType PowerUp::getType() { return this->_type; }
