#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "food.h"
#include "snake.h"

class Controller {
public:
  void HandleInput(bool &running, Snake &snake, Food &food) const;

private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif