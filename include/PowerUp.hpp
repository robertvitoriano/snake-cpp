#ifndef POWER_UP
#define POWER_UP
#include <GameConstants.h>
#include <SDL2/SDL.h>

class PowerUp {
 public:
  PowerUp();

  void render(SDL_Renderer *renderer, SDL_Texture *powerUpTexture);

  void update();
  void onHit();

  void checkCollision(const SDL_Rect &a, const SDL_Rect &b);

 private:
  Position _position;
  Size _size;
  SDL_Rect _powerUpRect;
};
#endif
