#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "food.h"
#include "renderer.h"
#include "snake.h"
#include "vector"

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

private:
  Snake snake;
  Food _food;

  int score{0};

  void PlaceFood();
  void Update();
};

// occupancy map of all objects on the game board
class GameMap {
public:
  std::vector<std::vector<uint>> map;

  void Update(Snake &snake, Food &food);

private:
};

#endif