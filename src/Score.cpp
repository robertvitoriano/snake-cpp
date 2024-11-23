#include "Score.h"

Score::Score() {
  foodSourceRect = {0, 32, 32, 32};
  rect = {40, 10, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  score = 0;
  if (TTF_Init() == -1) {
    SDL_Log("Failed to initialize SDL_ttf: %s", TTF_GetError());
  }
}

void Score::updateScore() { score++; }

void Score::render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture) {
  SDL_RenderCopy(renderer, spritesheetTexture, &foodSourceRect, &rect);

  TTF_Font *font = TTF_OpenFont("assets/fonts/BigBlueTermPlusNerdFontPropo-Regular.ttf", 24);
  if (!font) {
    SDL_Log("Failed to load font: %s", TTF_GetError());
    return;
  }

  std::string scoreText = "x " + std::to_string(score);

  SDL_Color textColor = {255, 255, 255};
  SDL_Surface *textSurface = TTF_RenderText_Blended(font, scoreText.c_str(), textColor);
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

  SDL_Rect textRect = {rect.x + rect.w + 10, rect.y, textSurface->w, textSurface->h};

  SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

  SDL_DestroyTexture(textTexture);
  TTF_CloseFont(font);
}
