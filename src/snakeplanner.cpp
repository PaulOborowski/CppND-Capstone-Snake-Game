#include "snakeplanner.h"
#include "debug.h"
#include "food.h"
#include <algorithm>
#include <cmath>
#include <iostream>

SnakePlanner::SnakePlanner(int width, int height) {
  DEBUG("SnakePlanner::SnakePlanner startet \n");
  // init board
  std::vector<std::vector<State>> initboard(
      height, std::vector<State>(width, State::kEmpty));
  _grid = initboard;

  DEBUG("SnakePlanner::SnakePlanner board size: " << _grid.size() << "  "
                                                  << _grid[0].size() << " \n");
};

SDL_Point SnakePlanner::Update(SDL_Point start, SDL_Point target,
                               std::vector<SDL_Point> obstacles) {

  // reset start and goal
  _init[0] = start.x;
  _init[1] = start.y;
  _goal[0] = target.x;
  _goal[1] = target.y;

  // reset board
  for (int x = 0; x < _grid.size(); x++) {
    for (int y = 0; y < _grid[0].size(); y++) {
      _grid[x][y] = State::kEmpty;
    }
  }
  // place start, target and obstacles
  _grid[_init[0]][_init[1]] = State::kStart;
  _grid[_goal[0]][_goal[1]] = State::kFinish;
  for (auto &item : obstacles) {
    _grid[item.x][item.y] = State::kObstacle;
  }
  DEBUG("SnakePlanner::Update: board resetted \n");

  // perform Search
  auto next = Search();
  PrintBoard();  
  // std::cin.ignore();
  target.x = next[0];
  target.y = next[1];
  return target;
};

void SnakePlanner::PrintBoard() {

  auto CellString = [](const SnakePlanner::State cell) {
    switch (cell) {
    case State::kObstacle:
      return "🐍   ";
    case State::kPath:
      return "🛣️   ";
    case State::kStart:
      return "🐲   ";
    case State::kFinish:
      return "🍲   ";
    case State::kClosed:
      return "❌   ";
    default:
      return "0   ";
    }
  };

  for (int i = 0; i < _grid.size(); i++) {
    for (int j = 0; j < _grid[i].size(); j++) {
      std::cout << CellString(_grid[j][i]);
    }
    std::cout << "\n";
  }
}

// Implementation of A* search algorithm
// ToDo: add feature to get the final path when using infinite number of steps search iterations
std::vector<int> SnakePlanner::Search() {

  // Create the vector of open nodes.
  _open.clear();

  // Initialize the starting node.
  int x = _init[0];
  int y = _init[1];
  int g = 0;
  int h = Heuristic(x, y, _goal[0], _goal[1]);
  int n = 0;
  AddToOpen(x, y, g, h);

  while (_open.size() > 0) {
    n++;

    // Get the next node
    CellSort();
    auto current = _open.back();
    _open.pop_back();
    x = current[0];
    y = current[1];
    _grid[x][y] = State::kPath;

    // Check if we're done.
    if (n>1) {
        DEBUG("run out of tries. \n");
        _grid[_init[0]][_init[1]] = State::kStart;
        _grid[_goal[0]][_goal[1]] = State::kFinish;
        return std::vector<int>{x, y};
    }
    if (x == _goal[0] && y == _goal[1]) {
      DEBUG("found solution. \n");
      _grid[_init[0]][_init[1]] = State::kStart;
      _grid[_goal[0]][_goal[1]] = State::kFinish;
      return std::vector<int>{x, y};
    }

    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(current);
  }

  // We've run out of new nodes to explore and haven't found a path.
  std::cout << "No path found! \n";
  return std::vector<int>{_goal[0], _goal[1]};
};

// Add a node to the open list and mark it as open.
void SnakePlanner::AddToOpen(int x, int y, int g, int h) {
  // Add node to open vector, and mark grid cell as closed.
  _open.push_back(std::vector<int>{x, y, g, h});
  _grid[x][y] = State::kClosed;
}

void SnakePlanner::ExpandNeighbors(const std::vector<int> &current) {
  // Get current node's data.
  int x = current[0];
  int y = current[1];
  int g = current[2];

  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++) {
    int x2 = x + _delta[i][0];
    int y2 = y + _delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and
    // not closed.
    if (CheckValidCell(x2, y2)) {
      // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, _goal[0], _goal[1]);
      AddToOpen(x2, y2, g2, h2);
    }
  }
}

// Check that a cell is valid: on the grid, not an obstacle, and clear.
bool SnakePlanner::CheckValidCell(int x, int y) {
  bool on_grid_x = (x >= 0 && x < _grid.size());
  bool on_grid_y = (y >= 0 && y < _grid[0].size());
  if (on_grid_x && on_grid_y) {
    return (_grid[x][y] == SnakePlanner::State::kEmpty ||
            _grid[x][y] == SnakePlanner::State::kFinish);
  }
  return false;
}