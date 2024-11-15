#include "Renderer.h"

Renderer::Renderer() : window(nullptr), renderer(nullptr), texture(nullptr) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    SDL_Quit();
    throw std::runtime_error("IMG_Init Error: " + std::string(IMG_GetError()));
  }
}

SDL_Renderer *Renderer::createRenderer(std::string gameName) {
  if (!renderer) {
    window = SDL_CreateWindow(gameName.c_str(), 100, 100, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
      destroyRenderer();
      throw std::runtime_error("SDL_CreateWindow Error: " +
                               std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
      destroyRenderer();
      throw std::runtime_error("SDL_CreateRenderer Error: " +
                               std::string(SDL_GetError()));
    }
  }

  return renderer;
}

Renderer::~Renderer() { destroyRenderer(); }

SDL_Texture *Renderer::createTexture(std::string imagePath) {
  if (!renderer) {
    throw std::runtime_error("Renderer not initialized.");
  }

  SDL_Surface *surface = IMG_Load(imagePath.c_str());
  if (!surface) {
    destroyRenderer();
    throw std::runtime_error("IMG_Load Error: " + std::string(IMG_GetError()));
  }

  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    destroyRenderer();
    throw std::runtime_error("SDL_CreateTextureFromSurface Error: " +
                             std::string(SDL_GetError()));
  }

  return texture;
}
void Renderer::destroyRenderer() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
  if (window) {
    SDL_DestroyWindow(window);
  }
  IMG_Quit();
  SDL_Quit();
}
