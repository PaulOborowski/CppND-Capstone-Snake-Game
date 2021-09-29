#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <iostream>
#include "globals.h"

  // init random number generator  
  std::random_device dev;
  std::mt19937 engine(dev());
  std::uniform_int_distribution<int> random_w(0,static_cast<int>(32 - 1));
  std::uniform_int_distribution<int> random_h(0,static_cast<int>(32 - 1));

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}