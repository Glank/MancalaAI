#ifndef GLANK_GAME_H
#define GLANK_GAME_H

#include "board.h"

#include <iostream>
#include <string>
#include <list>

namespace glank {
namespace mancala {

class Game {
 public:
  Game(std::ostream& out);
  void RunCommand(const std::string& cmd);
  void Reset();
  Board CurrentBoard() const;
  void PrintHelp() const;
 private:
  void TrimStack();
  void HumanMove(int move);
  std::list<Board> board_stack;
  std::ostream& out;
};

} // namespace mancala
} // namespace glank

#endif /* GLANK_GAME_H */
