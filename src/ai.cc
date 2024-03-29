#include "ai.h"

#include <limits>
#include <vector>

namespace glank {
namespace mancala {

int MinMax(const Board& board, int depth, Board* bestMove,
    int min_score_bound=std::numeric_limits<int>::min(),
    int max_score_bound=std::numeric_limits<int>::max()) {
  if (bestMove == nullptr) {
    throw std::runtime_error(
      "bestMove cannot be null");
  }
  if (depth <= 0 || board.IsTerminal()) {
    return board.GetScore();
  }
  std::vector<Board> moves;
  board.AppendMoves(&moves);
  Board bestNextMoves[
    moves.size()*(depth-1)];
  if (board.IsPlayer1Turn()) {
    int maxScore =
      MinMax(moves[0], depth-1, 
        &(bestNextMoves[0]));
    int bestIndex = 0;
    for (int i = 1; i < moves.size(); i++) {
      int score = MinMax(moves[i], depth-1,
        &(bestNextMoves[(depth-1)*i]), min_score_bound, max_score_bound);
      if (score > maxScore) {
        maxScore = score;
        bestIndex = i;
      }
      if (score > min_score_bound) {
        min_score_bound = score;
      }
      if (min_score_bound >= max_score_bound) {
        break;
      }
    }
    bestMove[0] = moves[bestIndex];
    for (int i = 0; i < depth-1; i++) {
      bestMove[i+1] =
        bestNextMoves[(depth-1)*bestIndex+i];
    }
    return maxScore;
  } else {
    int minScore =
      MinMax(moves[0], depth-1,
        &(bestNextMoves[0]));
    int bestIndex = 0;
    for (int i = 1; i < moves.size(); i++) {
      int score = MinMax(moves[i], depth-1,
        &(bestNextMoves[(depth-1)*i]), min_score_bound, max_score_bound);
      if (score < minScore) {
        minScore = score;
        bestIndex = i;
      }
      if (score < max_score_bound) {
        max_score_bound = score;
      }
      if (min_score_bound >= max_score_bound) {
        break;
      }
    }
    bestMove[0] = moves[bestIndex];
    for (int i = 0; i < depth-1; i++) {
      bestMove[i+1] =
        bestNextMoves[(depth-1)*bestIndex+i];
    }
    return minScore;
  }
}

Board GetBestMove(const Board& board,
  int depth, std::vector<Board>* thought) {
  Board out[depth];
  MinMax(board, depth, out);
  if (thought != nullptr) {
    for (int i = 0; i < depth; i++) {
      thought->push_back(out[i]);
    }
  }
  return out[0];
}

} // namespace mancala
} // namespace glank
