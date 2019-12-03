#ifndef GLANK_AI_H
#define GLANK_AI_H

#include "board.h"

namespace glank {
namespace mancala {

Board GetBestMove(const Board& board,
  int depth=4,
  std::vector<Board>* thought = nullptr);

} // namespace mancala
} // namespace glank

#endif /* GLANK_AI_H */
