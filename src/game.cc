#include "game.h"
#include "ai.h"

#include <sstream>

namespace glank {
namespace mancala {

constexpr int kMaxStackSize = 100000;

using std::string;

Game::Game(std::ostream& out) : out(out) {
  Reset();
};

Board Game::CurrentBoard() const {
  return board_stack.back();
}

void Game::Reset() {
  board_stack.clear();
  board_stack.push_back(Board::InitNew());
}

void Game::TrimStack() {
  while (board_stack.size() > kMaxStackSize) {
    board_stack.pop_front();
  }
}

void Game::HumanMove(int move) {
  if (move < 1 || move > 6) {
    out << "Invalid Move" << std::endl;
    return;
  }
  Board cur = CurrentBoard();
  int fromCell;
  if (cur.IsPlayer1Turn()) {
    fromCell = 7-move;
  } else {
    fromCell = 14-move;
  }
  if (!cur.IsValidMove(fromCell)) {
    out << "Invalid Move" << std::endl;
    return;
  }
  board_stack.push_back(cur.DoMove(fromCell));
}

void Game::PrintHelp() const {
  out << "  aimove (1-12)" << std::endl;
  out << "  ai (1-12)" << std::endl;
  out << "  move [1-6]" << std::endl;
  out << "  mv [1-6]" << std::endl;
  out << "  print" << std::endl;
  out << "  p" << std::endl;
  out << "  undo" << std::endl;
  out << "  reset" << std::endl;
  out << "  help" << std::endl;
  out << "  h" << std::endl;
  out << "  quit" << std::endl;
  out << "  q" << std::endl;
}

void Game::RunCommand(const std::string& cmd) {
  std::stringstream ss(cmd);
  string main_cmd;
  ss >> main_cmd;
  if (main_cmd == "aimove" || main_cmd == "ai") {
    int depth = 0;
    ss >> depth;
    if (depth < 0 || depth > 12) {
      out << "Invalid Argument" << std::endl;
    } else {
      if(depth == 0)
        depth = 4;
      board_stack.push_back(GetBestMove(CurrentBoard(), depth));
    }
  } else if (main_cmd == "reset") {
    Reset();
  } else if (main_cmd == "print" || main_cmd == "p") {
    out << CurrentBoard().DebugString() << std::endl;
  } else if (main_cmd == "help" || main_cmd == "h") {
    PrintHelp();
  } else if (main_cmd == "undo") {
    board_stack.pop_back();
  } else if (main_cmd == "move" || main_cmd == "mv") {
    int move = 0;
    ss >> move;
    HumanMove(move);
  } else if (main_cmd == "q" || main_cmd == "quit") {
    exit(0); 
  } else {
    out << "Invalid Command" << std::endl;
  }
  TrimStack();
}

} // namespace mancala
} // namespace glank
