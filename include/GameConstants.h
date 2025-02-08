#ifndef CONSTANTS_H
#define CONSTANTS_H

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BASIC_UNITY_SIZE = 32;
const int SNAKE_INITIAL_SPEED = 5;
const int SEGMENTS_LIMIT_TO_MOVE_BODY_FOWARD = 3;

struct Position {
  int x;
  int y;
};

struct Size {
  int width;
  int height;
};

#endif
