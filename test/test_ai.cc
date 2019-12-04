#include "ai.h"
#include "board.h"

#include <iostream>
#include <sstream>

namespace glank {
namespace mancala {

void AIFirstMoveTest() {
  std::cout << "AIFirstMoveTest..." << std::endl;
  Board board = Board::InitNew();
  std::vector<Board> thought;
  Board bestMove = GetBestMove(board, 8, &thought);
  std::string str = bestMove.DebugString();
  /*
  std::cout << str << std::endl;
  std::cout << std::endl;
  for (const Board& b: thought) {
    std::cout << b.DebugString() << std::endl;
  }
  // */

  std::stringstream ss;
  ss << "1 to 0 :::1:::" << std::endl;
  ss << "4 : 4 : 4 | 4 : 4 : 4" << std::endl;
  ss << "4 : 4 : 0 | 5 : 5 : 5";
  std::string expected = ss.str();
  if(str != expected) {
    exit(1);
  }
}

void AIFullGameTest() {
  std::cout << "AIFullGameTest..." << std::endl;
  Board board = Board::InitNew();
  while (!board.IsTerminal()) {
    //std::cout << board.DebugString() << std::endl;
    board = GetBestMove(board, 5);
  }
  //std::cout << board.DebugString() << std::endl;
}

} // namespace mancala
} // namespace glank

int main() {
  std::cout << "Testing..." << std::endl;
  glank::mancala::AIFirstMoveTest();
  glank::mancala::AIFullGameTest();
  std::cout << "All tests passed." << std::endl;
  return 0;
}
