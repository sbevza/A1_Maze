#ifndef A1_MAZE_1_SRC_MAZE_MODELS_MAZE_GENERATOR_H_
#define A1_MAZE_1_SRC_MAZE_MODELS_MAZE_GENERATOR_H_

#include <algorithm>
#include <random>
#include <unordered_map>

#include "maze.h"

namespace s21 {

struct Cell {
  bool rightWall = false;
  bool bottomWall = false;
  int setId = -1;
};

class MazeGenerator {
 public:
  explicit MazeGenerator(Maze &maze);
  bool generate();

 private:
  int counterId_ = 1;
  Maze &maze_;
  int rows_;
  int cols_;
  std::vector<std::vector<Cell>> matrix_;
  std::mt19937 gen_{std::random_device{}()};

  void joinCellsToUniqueSets(int currentRow);
  void createRightWalls(int currentRow);
  void createBottomWalls(int currentRow);
  void prepareNextRow(int currentRow);
  void completeMaze(int currentRow);
  void transferMaze();
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MAZE_MODELS_MAZE_GENERATOR_H_
