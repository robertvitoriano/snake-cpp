#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

enum XDirection { RIGHT, LEFT };
enum YDirection { UP, DOWN };

class Snake {
public:
  Snake(int xPos, int yPos);
  void moveY(int speed);
  void moveX(int speed);
  void increaseSize();
  const std::vector<SDL_Rect> &getBody() const;
  void render(SDL_Renderer *renderer, SDL_Texture *spritesheetTexture);

private:
  std::vector<SDL_Rect> body;
  void updateBodyPositions();
  double calculateAngle();
  YDirection yDirection;
  XDirection xDirection;
  int dx, dy;
};

#endif
