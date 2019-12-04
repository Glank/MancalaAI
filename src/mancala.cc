#include <iostream>
#include <string>
#include "game.h"

using namespace glank::mancala;
using namespace std;

int main() {
  Game game(cout);
  game.RunCommand("p");
  string line = "";
  while(true) {
    getline(cin, line);
    game.RunCommand(line);
  }
  return 0;
}
