#include "ai.h"
#include "board.h"
#include "game.h"

#include <iostream>
#include <sstream>

namespace glank {
namespace mancala {

void GameRunCommandTest() {
  std::cout << "GameRunCommandTest..." << std::endl;

  std::stringstream ss;
  Game game(ss);
  game.RunCommand("aimove");
  game.RunCommand("aimove -1");
  game.RunCommand("aimove 0");
  game.RunCommand("aimove 2");
  game.RunCommand("aimove 13");
  game.RunCommand("ai 1");
  game.RunCommand("move 0");
  game.RunCommand("move 1");
  game.RunCommand("move 6");
  game.RunCommand("move 7");
  game.RunCommand("mv 2");
  game.RunCommand("print");
  game.RunCommand("p");
  game.RunCommand("undo");
  game.RunCommand("reset");
  game.RunCommand("help");
  game.RunCommand("h");
  game.RunCommand("bla");
}

} // namespace mancala
} // namespace glank

int main() {
  std::cout << "Testing..." << std::endl;
  glank::mancala::GameRunCommandTest();
  std::cout << "All tests passed." << std::endl;
  return 0;
}
