#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "MusicPlayer.h"

enum Direction { UP, RIGHT, DOWN, LEFT };
struct SnakeSegment {
  SDL_Rect rect;
  double angle;
};

class Snake {
 public:
  Snake(int xPos, int yPos);
  const std::vector<SnakeSegment> &getBody() const;
  int getCurrentLives();
  void increaseSize();
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void handleHit();
  void update();

 private:
  void handleMovements();
  void checkForCollision();
  void renderSnakeBody(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void turnSnakeBodySegmentUp(int snakeBodyIndex, SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void handleBodyTurnUpAnimation(int snakeBodyIndex, SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  void renderSnakeHead(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);
  SDL_Rect getMouthRect(const SDL_Rect &headRect, Direction direction);
  void checkCollision(const SDL_Rect &a, const SDL_Rect &b);
  void moveY(int dy);
  void moveX(int dx);
  void handleHeadBodyHit();
  std::vector<SnakeSegment> body;
  SDL_Rect bodySourceRect;
  SDL_Rect cornerSourceRect;
  SDL_Rect headSourceRect;
  Direction direction;
  bool collidedWithWall;
  bool collidedWithBody;
  int lives;
  bool wasHit;
  Uint32 hitTimer;
  Uint32 hitInterval;
};

#endif
