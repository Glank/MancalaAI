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
  autoai1 = 0;
  autoai2 = 0;
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
  // Formatting note: the lines below should be no longer then 80 characters long which is
  // shown below:
  //     "01234567890123456789012345678901234567890123456789012345678901234567890123456789"
  out << "  quit" << std::endl;
  out << "  q" << std::endl;
  out << "  help" << std::endl;
  out << "  h" << std::endl;
  out << "  aimove (1-12) (v|verbose)" << std::endl;
  out << "  ai (1-12) (v|verbose)" << std::endl;
  out << "    Runs a single AI move at the given level (defaults to 4 if unspecified."
      << std::endl;
  out << "    If verbose is specified then the full thought trace will also be printed."
      << std::endl;
  out << "  move [1-6]" << std::endl;
  out << "  mv [1-6]" << std::endl;
  out << "    Performs a single move. The spaces are numbered from the current players"
      << std::endl;
  out << "    goal backwards, so the space closest to the current player's goal is 1 and"
      << std::endl;
  out << "    the furthest is 6." << std::endl;
  out << "  print" << std::endl;
  out << "  p" << std::endl;
  out << "  undo (#)" << std::endl;
  out << "    Undoes the specified number of moves. 1 by default." << std::endl;
  out << "  reset" << std::endl;
  out << "  pack" << std::endl;
  out << "    Prints a packaged board string that can be loaded with the 'unpack' command."
      << std::endl;
  out << "  unpack <packaged board>" << std::endl;
  out << "    Loads a packaged board from the output of a pack command. The format is a"
      << std::endl;
  out << "    list of all the cell's counts starting from the left most (player 2's gate)"
      << std::endl;
  out << "    going counter clockwise followed by '-' if the game is in a terminal state,"
      << std::endl;
  out << "    or 1 or 2 depending on the next player to move."
      << std::endl;
  out << "  autoprint [on|off]" << std::endl;
  out << "    If autoprint is on the board will be printed after each command and turn"
      << std::endl;
  out << "    automatically."
      << std::endl;
  out << "  autoai [1|2] [off|1-12]" << std::endl;
  out << "    If an auto ai is set then an ai move at the specified level will be"
      << std::endl;
  out << "    performed whenever the board is on player 1 or 2's turn (whichever is"
      << std::endl;
  out << "    specified). This AI is reset by the 'reset' command."
      << std::endl;
}

void Game::AIMove(const std::vector<std::string>& args) {
  int idx = 0;
  int depth = 0;
  bool verbose = false;
  // try to parse depth
  if (idx < args.size()) {
    try {
      depth = std::stoi(args[idx]);
      idx++;
    } catch (const std::invalid_argument& ia) {
      depth = 4;
    }
  }
  if (depth < 1 || depth > 12) {
    out << "Invalid Argument" << std::endl;
    return;
  }
  // try to verbose flag
  if (idx < args.size()) {
    if (args[idx] == "v" || args[idx] == "verbose") {
      verbose = true;
    } else {
      out << "Invalid Argument" << std::endl;
      return;
    }
    idx++;
  }
  // Fallthrough to catch too many arguments.
  if (idx < args.size()) {
    out << "Too Many Arguments" << std::endl;
    return;
  }
  std::vector<Board> thought;
  board_stack.push_back(GetBestMove(CurrentBoard(), depth, &thought));
  if (verbose) {
    out << "~~~AI Thought~~~" << std::endl;
    for (int i = 0; i < thought.size(); i++) {
      out << "~~~~~~ " << (i+1) << " ~~~~~~" << std::endl;
      out << thought[i].DebugString() << std::endl;
    }
    out << "~~~~~~~~~~~~~~~~" << std::endl;
  }
}

void Game::PrintCurrent() {
  out << CurrentBoard().DebugString() << std::endl;
}

void Game::Undo(int n) {
  if(n == 0)
    n = 1;
  while (board_stack.size() > 1 && n > 0) {
    board_stack.pop_back(); 
    n--;
  }
}

void Game::RunCommand(const std::string& cmd) {
  std::stringstream ss(cmd);
  string main_cmd;
  ss >> main_cmd;
  if (main_cmd == "aimove" || main_cmd == "ai") {
    std::vector<std::string> args(
      std::istream_iterator<std::string>{ss},
      std::istream_iterator<std::string>());
    AIMove(args);
  } else if (main_cmd == "reset") {
    Reset();
  } else if (main_cmd == "print" || main_cmd == "p") {
    PrintCurrent();
  } else if (main_cmd == "help" || main_cmd == "h") {
    PrintHelp();
  } else if (main_cmd == "undo") {
    int n = 0;
    ss >> n;
    Undo(n);
  } else if (main_cmd == "move" || main_cmd == "mv") {
    int move = 0;
    ss >> move;
    HumanMove(move);
  } else if (main_cmd == "q" || main_cmd == "quit") {
    exit(0); 
  } else if (main_cmd == "pack") {
    out << CurrentBoard().Pack() << std::endl;
  } else if (main_cmd == "unpack") {
    Board unpacked;
    std::string str;
    getline(ss, str);
    if (Board::Unpack(str, &unpacked)) {
      board_stack.clear();
      board_stack.push_back(unpacked);
    } else {
      out << "Invalid Package" << std::endl;
    }
  } else if (main_cmd == "autoprint") {
    std::string arg;
    ss >> arg;
    if (arg == "on") {
      autoprint = true;
    } else if (arg == "off") {
      autoprint = false;
    } else {
      out << "Invalid Argument" << std::endl;
    }
  } else if (main_cmd == "autoai") {
    std::string arg1, arg2;
    ss >> arg1;
    ss >> arg2;
    int setting = 0;
    if (arg2 == "off") {
      setting = 0;
    } else {
      try {
        setting = std::stoi(arg2);
      } catch (const std::invalid_argument& ia) {
        out << "Invalid Argument" << std::endl;
      }
    }
    if (arg1 == "1") {
      autoai1 = setting;
    } else if (arg1 == "2") {
      autoai2 = setting;
    } else {
      out << "Invalid Argument" << std::endl;
    }
  } else {
    out << "Invalid Command" << std::endl;
  }
  TrimStack();
  if (autoprint && main_cmd != "print" && main_cmd != "p") {
    PrintCurrent();
  }
  if (!CurrentBoard().IsTerminal()) {
    if (autoai1 && CurrentBoard().IsPlayer1Turn()) {
      std::stringstream cmd;
      cmd << "ai " << autoai1;
      RunCommand(cmd.str());
    } else if (autoai2 && !CurrentBoard().IsPlayer1Turn()) {
      std::stringstream cmd;
      cmd << "ai " << autoai2;
      RunCommand(cmd.str());
    }
  }
}

} // namespace mancala
} // namespace glank
