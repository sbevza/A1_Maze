#include "maze_solver.h"

namespace s21 {

bool operator==(const Point &a, const Point &b) {
  return a.x == b.x && a.y == b.y;
}

bool operator!=(const Point &a, const Point &b) { return !(a == b); }

bool operator<(const Point &a, const Point &b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

MazeSolver::MazeSolver(const Maze &maze) : maze_(maze) {}

std::vector<s21::Point> MazeSolver::findPath(int x1, int y1, int x2, int y2) {
  Point start = {x1 - 1, y1 - 1};
  Point end = {x2 - 1, y2 - 1};
  return bfs(start, end);
}

std::vector<Point> MazeSolver::bfs(const Point &start, const Point &end) {
  std::vector<std::vector<bool>> visited(
      maze_.getRightWalls().size(),
      std::vector<bool>(maze_.getRightWalls()[0].size(), false));
  std::queue<Point> queue;
  std::map<Point, Point> prev;
  std::vector<Point> path;
  bool found = false;

  queue.push(start);
  visited[start.y][start.x] = true;
  std::vector<Point> directions = {
      {0, 1}, {1, 0}, {0, -1}, {-1, 0}};  // Вниз, вправо, вверх, влево

  while (!queue.empty() && !found) {
    Point current = queue.front();
    queue.pop();

    if (current == end) {
      found = true;
      for (Point at = end; at != start; at = prev[at]) {
        path.push_back(at);
      }
      path.push_back(start);
      std::reverse(path.begin(), path.end());
    }

    if (!found) {
      for (const Point &direction : directions) {
        Point next = {current.x + direction.x, current.y + direction.y};
        if (canMove(current, next) && !visited[next.y][next.x]) {
          queue.push(next);
          visited[next.y][next.x] = true;
          prev[next] = current;
        }
      }
    }
  }
  return path;
}

bool MazeSolver::canMove(const Point &current, const Point &next) {
  bool canMoveFlag = false;
  bool isWithinBounds =
      static_cast<size_t>(next.y) < maze_.getRightWalls().size() &&
      static_cast<size_t>(next.x) < maze_.getRightWalls()[0].size();

  if (isWithinBounds) {
    if (current.x == next.x) {
      if (current.y < next.y) {  // Вниз
        canMoveFlag = !maze_.getBottomWalls()[current.y][current.x];
      } else if (current.y > next.y) {  // Вверх
        canMoveFlag = current.y > 0 && !maze_.getBottomWalls()[next.y][next.x];
      }
    } else if (current.y == next.y) {
      if (current.x < next.x) {  // Вправо
        canMoveFlag = !maze_.getRightWalls()[current.y][current.x];
      } else if (current.x > next.x) {  // Влево
        canMoveFlag = current.x > 0 && !maze_.getRightWalls()[next.y][next.x];
      }
    }
  }

  return canMoveFlag;
}

}  // namespace s21