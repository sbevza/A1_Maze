#ifndef A1_MAZE_1_SRC_MAZE_MODELS_MAZE_SOLVER_H_
#define A1_MAZE_1_SRC_MAZE_MODELS_MAZE_SOLVER_H_

#include <algorithm>
#include <map>
#include <queue>
#include <vector>

#include "maze.h"

namespace s21 {

struct Point {
  int x, y;
};

bool operator==(const Point &a, const Point &b);
bool operator!=(const Point &a, const Point &b);
bool operator<(const Point &a, const Point &b);

class MazeSolver {
 public:
  explicit MazeSolver(const Maze &maze);
  std::vector<s21::Point> findPath(int x1, int y1, int x2, int y2);

 private:
  const Maze &maze_;
  bool canMove(const Point &current, const Point &next);
  std::vector<Point> bfs(const Point &start, const Point &end);
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MAZE_MODELS_MAZE_SOLVER_H_
