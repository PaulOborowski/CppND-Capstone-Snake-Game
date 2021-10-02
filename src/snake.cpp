#include "snake.h"
#include "debug.h"
#include "food.h"
#include <algorithm>
#include <cmath>
#include <iostream>

// ****************************************************************
// class Snake
// ****************************************************************

void Snake::Update(SDL_Point target) {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.

  if (autoSteer == true) {
    // ToDo: implement low level obstacle avoidance
    
    DEBUG("start: " << prev_cell.x << " " << prev_cell.y << std::endl);
    DEBUG("goal: " << target.x << " " << target.y << std::endl);
    target = _snakePlanner.Update(prev_cell, target, body);
    DEBUG("next: " << target.x << " " << target.y << std::endl);
    
    if (target.x == prev_cell.x) {
      // go either up or down
      if (target.y < prev_cell.y) {
        direction = Direction::kUp;
        DEBUG("automated steering: up " << std::endl);
      } else {
        direction = Direction::kDown;
        DEBUG("automated steering: down " << std::endl);
      }
    } else {
      // go either left or right
      if (target.x < prev_cell.x) {
        direction = Direction::kLeft;
        DEBUG("automated steering: left " << std::endl);
      } else {
        direction = Direction::kRight;
        DEBUG("automated steering: right " << std::endl);
      }
    }
    /*
       // target deviation in x and y
       float devX = target.x - prev_cell.x;
       float devY = target.y - prev_cell.y;
       DEBUG("head_x: " << head_x << "head_y: " << head_y << std::endl);
       DEBUG("devX: " << devX << "devY: " << devY << std::endl);

       // apply direction change to reduce biggest deviation
       if (abs(devX) > abs(devY)) {
         if (devX > 0) {
           direction = Direction::kRight;
           DEBUG("automated steering: right " << std::endl);
         } else {
           direction = Direction::kLeft;
           DEBUG("automated steering: left " << std::endl);
         }
       } else {
         if (devY < 0) {
           direction = Direction::kUp;
           DEBUG("automated steering: up " << std::endl);
         } else {
           direction = Direction::kDown;
           DEBUG("automated steering: down " << std::endl);
         }
       }
       */
  }

  UpdateHead();

  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {

  // user steers snake
  switch (direction) {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell,
                       SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}
