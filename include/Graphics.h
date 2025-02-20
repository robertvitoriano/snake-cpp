#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>
#include <string>

#include "GameConstants.h"

class Graphics {
 public:
  Graphics();
  ~Graphics();
  void destroyRenderer();
  SDL_Renderer *createRenderer(std::string gameName);
  SDL_Texture *createTexture(std::string imagePath);
  void drawText(std::string text, SDL_Color color, Position position, SDL_Renderer *renderer);

 private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
};

#endif
