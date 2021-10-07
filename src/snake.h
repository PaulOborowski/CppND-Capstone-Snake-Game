#ifndef SNAKE_H
#define SNAKE_H

#include "SDL.h"
#include "snakeplanner.h"
#include <algorithm>
#include <vector>

class Snake {
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width), grid_height(grid_height),
        head_x(grid_width / 2), head_y(grid_height / 2),
        _snakePlanner(grid_width, grid_height) {}

  void Update(SDL_Point target);

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  // snake steers itself without user input
  bool autoSteer = false;

private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  SnakePlanner _snakePlanner;

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif