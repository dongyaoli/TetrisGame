#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{384};
  constexpr std::size_t kScreenHeight{758};
  constexpr std::size_t kGridSize(32);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridSize);
  Controller controller;
  Game game(kGridSize, kScreenWidth, kScreenHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  return 0;
}