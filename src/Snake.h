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
  void handleMovements();
  void increaseSize();
  const std::vector<SnakeSegment> &getBody() const;
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  bool hasLost();

 private:
  void renderSnakeBody(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void turnSnakeBodySegmentUp(int snakeBodyIndex, SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void handleBodyTurnUpAnimation(int snakeBodyIndex, SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void renderSnakeHead(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void moveY(int dy);
  void moveX(int dx);
  std::vector<SnakeSegment> body;
  SDL_Rect bodySourceRect;
  SDL_Rect cornerSourceRect;
  SDL_Rect headSourceRect;
  Direction direction;
  bool collidedWithWall;
  bool collidedWithBody;
};

#endif
