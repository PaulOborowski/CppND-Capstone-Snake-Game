#include "controller.h"
#include "SDL.h"
#include "debug.h"
#include "snake.h"
#include <iostream>

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, Food &food) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(snake, Snake::Direction::kLeft,
                        Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake, Snake::Direction::kRight,
                        Snake::Direction::kLeft);
        break;

        // handle controls of food
      case SDLK_w:
        DEBUG("Move food up \n");
        food.direction = Food::Direction::kUp;
        break;

      case SDLK_s:
        DEBUG("Move food down \n");
        food.direction = Food::Direction::kDown;
        break;

      case SDLK_a:
        DEBUG("Move food left \n");
        food.direction = Food::Direction::kLeft;
        break;

      case SDLK_d:
        DEBUG("Move food right \n");
        food.direction = Food::Direction::kRight;
        break;
      }
    } else if (e.type == SDL_KEYUP) {
      // hold position of food if no button pressed
      DEBUG("stop moving food \n");
      food.direction = Food::Direction::kHold;
    }
  }
}