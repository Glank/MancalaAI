#include "board.h"

#include <iostream>
#include <sstream>

namespace glank {
namespace mancala {

void BoardPrintTest() {
  std::cout << "BoardPrintTest..." << std::endl;
  Board board = Board::InitNew();
  std::string str = board.DebugString();
  std::stringstream ss;
  ss << "0 to 0 :::1:::" << std::endl;
  ss << "4 : 4 : 4 | 4 : 4 : 4" << std::endl;
  ss << "4 : 4 : 4 | 4 : 4 : 4";
  std::string expected = ss.str();
  if(str != expected) {
    exit(1);
  }
}

void BoardDoMovesTest() {
  std::cout << "BoardDoMovesTest..." << std::endl;
  Board board = Board::InitNew();
  board = board.DoMoves({
    3, 6, 9, 13, 2, 6,
    1, 12, 3, 6, 5, 13,
    6, 1, 10, 1, 13, 12,
    13, 9, 2, 6, 4, 8, 3,
    11, 4, 12, 5, 6});
  std::string str = board.DebugString();
  //std::cout << str << std::endl;

  std::stringstream ss;
  ss << "26 to 22 :::-:::" << std::endl;
  ss << "0 : 0 : 0 | 0 : 0 : 0" << std::endl;
  ss << "0 : 0 : 0 | 0 : 0 : 0";
  std::string expected = ss.str();
  if(str != expected) {
    exit(1);
  }
}

void BoardPackUnpackTest() {
  std::cout << "BoardPackUnpackTest..." << std::endl;
  Board board = Board::InitNew();
  std::string packed = board.Pack();
  Board unpacked;
  if (!Board::Unpack(packed, &unpacked)) {
    exit(1);
  }

  if (!Board::Unpack(
      "0 1 2 3 4 5 6 7 8 9 10 11 12 13 1", &unpacked)) {
    exit(1);
  }
  std::stringstream ss;
  ss << "7 to 0 :::1:::" << std::endl;
  ss << "13 : 12 : 11 | 10 : 9 : 8" << std::endl;
  ss << "1 : 2 : 3 | 4 : 5 : 6";
  std::string expected = ss.str();
  if(unpacked.DebugString()!= expected) {
    exit(1);
  }
}

} // namespace mancala
} // namespace glank

int main() {
  std::cout << "Testing..." << std::endl;
  glank::mancala::BoardPrintTest();
  glank::mancala::BoardDoMovesTest();
  glank::mancala::BoardPackUnpackTest();
  std::cout << "All tests passed." << std::endl;
  return 0;
}
