#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include "globals.h"
#include "snake.h"
class Food {

public:
  void Place(Snake &snake);

  SDL_Point GetLoc();

private:
  // location of food
  SDL_Point _pos;
};

#endif