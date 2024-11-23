#include "Score.h"

Score::Score() {
  foodSourceRect = {0, 32, 32, 32};
  rect = {40, 10, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
}

void Score::updateScore() {}
void Score::render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture) {
  SDL_RenderCopy(renderer, spritesheetTexture, &foodSourceRect, &rect);
}
