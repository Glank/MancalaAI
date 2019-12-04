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
  //*
  game.RunCommand("autoai 1 5");
  game.RunCommand("autoai 1 off");
  game.RunCommand("autoprint off");
  game.RunCommand("autoai 2 4");
  game.RunCommand("autoprint on");
  game.RunCommand("aimove 3 v");
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
  game.RunCommand("undo -1");
  game.RunCommand("undo 5");
  game.RunCommand("reset");
  game.RunCommand("help");
  game.RunCommand("h");
  game.RunCommand("bla");
  game.RunCommand("unpack 0 1 2 3 4 5 6 7 8 9 10 11 12 13 1");
  game.RunCommand("print");
  // */
  //std::cout << ss.str() << std::endl;
}

} // namespace mancala
} // namespace glank

int main() {
  std::cout << "Testing..." << std::endl;
  glank::mancala::GameRunCommandTest();
  std::cout << "All tests passed." << std::endl;
  return 0;
}
