#include "board.h"

#include <sstream>

namespace glank {
namespace mancala {

Board Board::InitNew() {
  Board b;
  b.player1Turn = true;
  b.terminal = false;
  for (int i = 1; i < 14; i++)
    b.cells[i] = 4;
  b.cells[0] = 0;
  b.cells[7] = 0;
  return b;
}

std::string Board::DebugString() const {
  std::stringstream tmp;  
  tmp << cells[7] << " to " << cells[0];
  std::string turn;
  if (terminal) {
    turn = "-";
  } else {
    turn = player1Turn ? "1" : "2";
  }
  tmp << " :::" << turn << ":::";
  tmp << std::endl;
  for (int i = 13; i >= 8; i--) {
    tmp << cells[i];
    if (i != 8)
      tmp << (i==11?" | ":" : ");
  }
  tmp << std::endl;
  for (int i = 1; i <= 6; i++) {
    tmp << cells[i];
    if (i != 6)
      tmp << (i==3?" | ":" : ");
  }
  return tmp.str();
}

bool Board::IsValidMove(int fromCell) const {
  if (terminal) {
    return false;
  }
  if (player1Turn) {
    if (fromCell < 1 || fromCell > 6) {
      return false;
    }
  } else { 
    if (fromCell < 8 || fromCell > 13) {
      return false;
    }
  }
  if (cells[fromCell] == 0) {
    return false;
  }
  return true;
}

Board Board::DoMove(int fromCell) const {
  Board out = *this;
  if (out.terminal) {
    throw std::runtime_error(
      "Cannot move in terminal state.");
  }
  if (!out.IsValidMove(fromCell)) {
      throw std::runtime_error(
        "Invalid From Cell");
  }
  int tmp = out.cells[fromCell];
  out.cells[fromCell] = 0;
  int index = fromCell;
  while(tmp > 0) {
    index = (index+1) % 14;
    if (player1Turn && index == 0)
      index++;
    if (!player1Turn && index == 7)
      index++;

    out.cells[index]++;
    tmp--;
  }
  // If you end in a goal, don't go to
  // the next player's turn.
  bool incrementTurn = true;
  if (index == 0 || index == 7) {
    incrementTurn = false;
  } else {
    // If you end in an empty cell, take
    // all of the adjacent cell.
    // If you land in your own side and
    // the adjacent cell isn't empty.
    bool isInOwnSide =
      player1Turn ?
        1 <= index && index <= 6:
        8 <= index && index <= 13;
    const int goal = player1Turn?7:0;
    const int adjacent = 14-index;
    if (isInOwnSide && out.cells[index] == 1
        && out.cells[adjacent] != 0) {
      out.cells[goal] +=
        out.cells[index] +
        out.cells[adjacent];
      out.cells[index] = 0;
      out.cells[adjacent] = 0;
    }
  }
  // Check to see if the game is terminal
  // and if so, collect all the full side's
  // tokens in it's goal.
  bool side1Empty = true;
  for (int i = 1; i<=6; i++) {
    if (out.cells[i] > 0) {
      side1Empty = false;
      break;
    }
  }
  bool side2Empty = true;
  for (int i = 8; i<=13; i++) {
    if (out.cells[i] > 0) {
      side2Empty = false;
      break;
    }
  }
  if (side1Empty && !side2Empty) {
    for (int i = 8; i <= 13; i++) {
      out.cells[0] += out.cells[i];
      out.cells[i] = 0;
    }
  }
  if (side2Empty && !side1Empty) {
    for (int i = 1; i <= 6; i++) {
      out.cells[7] += out.cells[i];
      out.cells[i] = 0;
    }
  }
  if (side1Empty || side2Empty) {
    out.terminal = true;
  }
  if (incrementTurn) {
    out.player1Turn = !out.player1Turn;
  }
  return out;
}

Board Board::DoMoves(
  std::vector<int> fromCells) const {
  Board cur = *this;
  for(int move : fromCells) {
    cur = cur.DoMove(move);
  }
  return cur;
}

bool Board::IsTerminal() const {
  return terminal;
}
void Board::AppendMoves(
  std::vector<Board>* out) const {
  if (terminal) {
    throw std::runtime_error(
      "Cannot append moves from terminal "
      "board state.");
  }
  if (player1Turn) {
    for (int i = 1; i <= 6; i++) {
      if (cells[i] > 0) {
        out->push_back(DoMove(i));
      }
    }
  } else {
    for (int i = 13; i >= 8; i--) {
      if (cells[i] > 0) {
        out->push_back(DoMove(i));
      }
    }
  }
}

int Board::GetScore() const {
  return cells[7]-cells[0];
}

bool Board::IsPlayer1Turn() const {
  return player1Turn;
}

std::string Board::Pack() const {
  std::stringstream ss;
  for (int i = 0; i < 14; i++) {
    ss << cells[i] << " ";
  }
  ss << (terminal ? '-' : (player1Turn ? '1' : '2'));
  return ss.str();
}
bool Board::Unpack(const std::string& str, Board* out) {
  if (out == nullptr) {
    return false;
  }
  std::stringstream ss(str);
  for (int i = 0; i < 14; i++) {
    ss >> out->cells[i];
    if (out->cells[i] < 0 || out->cells[i] > 4*6) {
      return false;
    }
  }
  std::string stat;
  ss >> stat;
  if (stat == "-") {
    out->terminal = true;
    out->player1Turn = false;
  } else if (stat == "1") {
    out->terminal = false;
    out->player1Turn = true;
  } else if (stat == "2") {
    out->terminal = false;
    out->player1Turn = false;
  } else {
    return false;
  }
  return true;
}

} // namespace mancala
} // namespace glank
