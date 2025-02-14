#ifndef POWER_UP
#define POWER_UP
#include <GameConstants.h>
#include <SDL2/SDL.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

class PowerUp {
 public:
  PowerUp(int id, std::string imageSrc, PowerUpType type, int timeToShow);

  void render(SDL_Renderer *renderer, SDL_Texture *powerUpTexture);

  void update();
  void onHit();

  void checkCollision(const SDL_Rect &a, const SDL_Rect &b);
  std::string getImageSrc();
  PowerUpType getType();
  int getTimeToShow();
  bool isOutOfScreen();
  const SDL_Rect &getRect();
  bool isDestroyed();
  void destroy();

 private:
  Position _position;
  Size _size;
  SDL_Rect _powerUpRect;
  std::string _imageSrc;
  PowerUpType _type;
  int _timeToShow;
  int _id;
  bool _wasDestroyed;
};
#endif
