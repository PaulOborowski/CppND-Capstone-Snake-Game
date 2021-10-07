#ifndef SNAKEPLANNER_H
#define SNAKEPLANNER_H

#include "SDL.h"
#include <algorithm>
#include <vector>

// ****************************************************************
// class SnakePlanner
// ****************************************************************

// classes for autosteer feature of snake based on idea of Astar search
class SnakePlanner {
public:
  enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };

  // init
  SnakePlanner(int width, int height);

  // Update  function called every iteration
  SDL_Point Update(SDL_Point &start, SDL_Point &target,
                   std::vector<SDL_Point> &obstacles);

  // print board for debuging
  void PrintBoard();

private:
  // perform search
  std::vector<int> Search();

  // Calculate the manhattan distance
  int Heuristic(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
  };

  // sort list function
  void CellSort() { std::sort(_open.begin(), _open.end(), Compare); };

  // Compare the F values of two cells
  static bool Compare(const std::vector<int> a, const std::vector<int> b) {
    int f1 = a[2] + a[3]; // f1 = g1 + h1
    int f2 = b[2] + b[3]; // f2 = g2 + h2
    return f1 > f2;
  }

  // Add a node to the open list and mark it as open.
  void AddToOpen(int x, int y, int g, int h);

  // add neighbors to open list
  void ExpandNeighbors(const std::vector<int> &current);

  // Check that a cell is valid: on the grid, not an obstacle, and clear.
  bool CheckValidCell(int x, int y);

  // grid map
  std::vector<std::vector<State>> _grid;

  // start
  int _init[2];

  // goal
  int _goal[2];

  // openlist
  std::vector<std::vector<int>> _open{};

  // directional deltas
  const int _delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
};

#endif