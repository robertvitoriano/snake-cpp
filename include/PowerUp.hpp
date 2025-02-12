#ifndef POWER_UP
#define POWER_UP
#include <GameConstants.h>
#include <SDL2/SDL.h>

#include <iostream>

class PowerUp {
 public:
  PowerUp(std::string imageSrc, PowerUpType type);

  void render(SDL_Renderer *renderer, SDL_Texture *powerUpTexture);

  void update();
  void onHit();

  void checkCollision(const SDL_Rect &a, const SDL_Rect &b);
  std::string getImageSrc();
  PowerUpType getType();

 private:
  Position _position;
  Size _size;
  SDL_Rect _powerUpRect;
  std::string _imageSrc;
  PowerUpType _type;
};
#endif
