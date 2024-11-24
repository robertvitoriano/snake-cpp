#include "Renderer.h"

Renderer::Renderer() : window(nullptr), renderer(nullptr), texture(nullptr) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    SDL_Quit();
    throw std::runtime_error("IMG_Init Error: " + std::string(IMG_GetError()));
  }
  if (TTF_Init() == -1) {
    throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
  }
}

SDL_Renderer *Renderer::createRenderer(std::string gameName) {
  if (!renderer) {
    window = SDL_CreateWindow(gameName.c_str(), 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
      destroyRenderer();
      throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
      destroyRenderer();
      throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
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
    throw std::runtime_error("SDL_CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
  }

  return texture;
}

void Renderer::drawText(std::string text, SDL_Color color, Position position, SDL_Renderer *renderer) {
  TTF_Font *font = TTF_OpenFont("assets/fonts/BigBlueTermPlusNerdFontPropo-Regular.ttf", 24);
  if (!font) {
    SDL_Log("Failed to load font: %s", TTF_GetError());
    return;
  }

  SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
  if (!textSurface) {
    SDL_Log("Failed to create text surface: %s", TTF_GetError());
    TTF_CloseFont(font);
    return;
  }

  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_FreeSurface(textSurface);

  if (!textTexture) {
    SDL_Log("Failed to create text texture: %s", SDL_GetError());
    TTF_CloseFont(font);
    return;
  }

  SDL_Rect textRect = {position.x - textSurface->w / 2, position.y - textSurface->h / 2, textSurface->w,
                       textSurface->h};

  SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

  SDL_DestroyTexture(textTexture);
  TTF_CloseFont(font);
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
