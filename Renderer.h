#ifndef RENDERER_H
#define RENDERER_H
#include "GameConstants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <string>

class Renderer {
public:
  Renderer();
  ~Renderer();
  void destroyRenderer();
  SDL_Renderer *createRenderer(std::string gameName);
  SDL_Texture *createTexture(std::string imagePath);

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
};

#endif
