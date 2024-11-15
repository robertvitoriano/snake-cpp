#include "Snake.h"
#include "GameConstants.h"

Snake::Snake(int xPos, int yPos) {

  SDL_Rect head = {xPos, yPos, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE};

  body.push_back(head);
}

void Snake::render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture) {

  if (body.empty()) {
    return;
  }

  SDL_Rect snakeHeadSrcRect = {32, 32, 32, 32};

  SDL_RenderCopy(renderer, spritesheetTexture, &snakeHeadSrcRect, &body[0]);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (size_t i = 1; i < body.size(); ++i) {
    SDL_RenderFillRect(renderer, &body[i]);
  }
}

void Snake::moveY(int dy) {
  for (size_t index = 0; index < body.size(); ++index) {

    SDL_Rect &segment = body[index];
    if (segment.y < 0) {
      segment.y = 0;
      continue;
    }
    if (segment.y > WINDOW_HEIGHT - BASIC_UNITY_SIZE) {
      segment.y = WINDOW_HEIGHT - BASIC_UNITY_SIZE;
      continue;
    }

    segment.y += dy;
    std::cout << "Index: " << index << ", Y: " << segment.y << "\n";
  }
}
void Snake::moveX(int dx) {

  for (size_t index = 0; index < body.size(); ++index) {

    SDL_Rect &segment = body[index];

    if (index == 0) {
      segment.x += dx;
      continue;
    }

    if (segment.x < 0) {
      segment.x = 0;
    }
    if (segment.x >= WINDOW_WIDTH - BASIC_UNITY_SIZE) {
      segment.x = WINDOW_WIDTH - BASIC_UNITY_SIZE;
    }
    if (dx > 0) {
      segment.x =
          body[index - 1].x - BASIC_UNITY_SIZE - SPACE_BETWEEN_BODY_PARTS;
    }
    if (dx < 0) {
      segment.x =
          body[index - 1].x + BASIC_UNITY_SIZE + SPACE_BETWEEN_BODY_PARTS;
    }

    segment.x += dx;

    std::cout << "Index: " << index << ", x: " << segment.x << "\n";
  }
}
const std::vector<SDL_Rect> &Snake::getBody() const { return body; }

void Snake::handleFoodEating() {
  body.push_back({body[body.size() - 1].x - BASIC_UNITY_SIZE * body.size(),
                  body[0].y, BASIC_UNITY_SIZE, BASIC_UNITY_SIZE});
}

void Snake::updateBodyPositions() {}
