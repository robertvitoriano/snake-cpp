#include "Score.h"

Score::Score() {
  foodSourceRect = {0, 32, 32, 32};
  rect = {40, 10, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  score = 0;
}

void Score::updateScore() { score++; }

void Score::render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture) {
  SDL_RenderCopy(renderer, spritesheetTexture, &foodSourceRect, &rect);

  std::string scoreText = "x " + std::to_string(score);
  SDL_Color textColor = {255, 255, 255};
  Position textPostion = {rect.x + 10, rect.y};
  gameRenderer.drawText(scoreText, textColor, textPostion, renderer);
}
