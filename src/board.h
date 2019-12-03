#ifndef GLANK_BOARD_H
#define GLANK_BOARD_H

#include <string>
#include <vector>

namespace glank {
namespace mancala {

//    13 12 11 10 09 08
// 00                   07
//    01 02 03 04 05 06
class Board {
 public:
  Board() = default;
  static Board InitNew();
  bool IsValidMove(int fromCell) const;
  Board DoMove(int fromCell) const;
  Board DoMoves(std::vector<int> fromCells)
    const;
  bool IsTerminal() const;
  void AppendMoves(std::vector<Board>* out)
    const;
  int GetScore() const;
  bool IsPlayer1Turn() const;
  std::string DebugString() const;
 private:
  bool player1Turn;
  bool terminal;
  int cells[14];
};

} // namespace mancala
} // namespace glank

#endif /* GLANK_BOARD_H */
