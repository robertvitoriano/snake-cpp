#include "UI.h"

UI::UI() : lives(0) {
  foodSourceRect = {0, 32, 32, 32};
  rect = {40, 10, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
  score = 0;
}

void UI::updateScore() { score++; }
int UI::getCurrentScore() { return this->score; }
void UI::setLives(int snakeLives) { lives = snakeLives; }

void UI::render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture, SDL_Texture *heartTexture) {
  SDL_RenderCopy(renderer, spritesheetTexture, &foodSourceRect, &rect);

  for (int i = 0; i < lives; i++) {
    SDL_Rect heartRect = {WINDOW_WIDTH - 50 - BASIC_UNITY_SIZE * i, 10, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};
    SDL_Rect heartSourceRect = {0, 0, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

    SDL_RenderCopy(renderer, heartTexture, &heartSourceRect, &heartRect);
  }

  std::string scoreText = "x " + std::to_string(score) + "/" + std::to_string(this->scoreGoal);
  SDL_Color textColor = {255, 255, 255};
  Position textPostion = {rect.x + 80, rect.y + 15};

  gameRenderer.drawText(scoreText, textColor, textPostion, renderer);
}

void UI::setScoreGoal(int scoreGoal) { this->scoreGoal = scoreGoal; }
void UI::resetScore() { this->score = 0; }
