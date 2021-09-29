#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include "globals.h"
#include "snake.h"
#include <vector>

class Food {

public:
  Food(int grid_width, int grid_height);

  enum class Direction { kUp, kDown, kLeft, kRight, kHold };

  void Place(Snake &snake);

  SDL_Point GetLoc();

  // move into direction, init with hold
  Direction direction = Direction::kHold;

  // update position of food
  void Update();

private:
  // location of food in grid
  SDL_Point _pos;

  // high res position
  double _pos_x;
  double _pos_y;

  // location change increment per button press
  double _posInc = 0.2;

  // location range
  int _grid_width;
  int _grid_height;
};

#endif