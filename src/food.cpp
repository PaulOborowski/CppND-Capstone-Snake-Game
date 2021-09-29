#include "food.h"
#include "SDL.h"
#include "debug.h"
#include "globals.h"

Food::Food(int grid_width, int grid_height)
    : _grid_width(grid_width), _grid_height(grid_height){

                               };

void Food::Place(Snake &snake) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      _pos.x = x;
      _pos.y = y;
      _pos_x = x;
      _pos_y = y;

      DEBUG("Placed green food at x: " << x << " y: " << y);

      return;
    }
  }
};

SDL_Point Food::GetLoc() { return _pos; };

void Food::Update() {
  float x, y;

  int dirChange[2]; // x, y change

  switch (direction) {
  case Direction::kUp:
    dirChange[0] = 0;
    dirChange[1] = -1;
    break;
  case Direction::kDown:
    dirChange[0] = 0;
    dirChange[1] = 1;
    break;
  case Direction::kLeft:
    dirChange[0] = -1;
    dirChange[1] = 0;
    break;
  case Direction::kRight:
    dirChange[0] = 1;
    dirChange[1] = 0;
    break;
  case Direction::kHold:
    dirChange[0] = 0;
    dirChange[1] = 0;
    break;
  }

  // update high res position
  _pos_x += dirChange[0] * _posInc;
  _pos_y += dirChange[1] * _posInc;

  // wrap around to the beginning if going off the screen.
  _pos_x = fmod(_pos_x + _grid_width, _grid_width);
  _pos_y = fmod(_pos_y + _grid_height, _grid_height);

  // update low res position for render
  _pos.x = (int)_pos_x;
  _pos.y = (int)_pos_y;

  return;
};
