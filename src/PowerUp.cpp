#include <PowerUp.hpp>

PowerUp::PowerUp() : _position({0, 0}), _size({BASIC_UNITY_SIZE, BASIC_UNITY_SIZE}) {
  this->_position.x = WINDOW_WIDTH / 2;
}

void PowerUp::update() { this->_position.y += 1; }

void PowerUp::onHit() {}

void PowerUp::render(SDL_Renderer *renderer, SDL_Texture *powerUpTexture) {
  SDL_Rect powerUpRect = {this->_position.x, this->_position.y, this->_size.width, this->_size.height};
  SDL_Rect powerUpSourceRect = {0, 0, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

  SDL_RenderCopy(renderer, powerUpTexture, &powerUpSourceRect, &powerUpRect);
}
