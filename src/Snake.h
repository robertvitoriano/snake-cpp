#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

enum Direction { UP, RIGHT, DOWN, LEFT };
struct SnakeSegment {
  SDL_Rect rect;
  double angle;
};

class Snake {
 public:
  Snake(int xPos, int yPos);
  void moveY(int dy);
  void moveX(int dx);
  void increaseSize();
  const std::vector<SnakeSegment> &getBody() const;
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);

 private:
  std::vector<SnakeSegment> body;
  SDL_Rect bodySourceRect;
  void renderSnakeBody(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void turnSnakeBodySegmentUp(int snakeBodyIndex, SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void handleBodyTurnUpAnimation(int snakeBodyIndex, SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  Direction direction;
  Uint32 timeStartedToTurnUp;
  Uint32 timeStartedToTurnDown;

  Uint32 turnUpDelay;
};

#endif
