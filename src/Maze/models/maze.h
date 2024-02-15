#ifndef A1_MAZE_1_SRC_MAZE_MODELS_MAZE_H_
#define A1_MAZE_1_SRC_MAZE_MODELS_MAZE_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {

class Maze {
 public:
  Maze() = default;

  bool loadFromFile(const std::string &filePath);
  bool saveToFile(const std::string &filePath);

  [[nodiscard]] int getRows() const;
  [[nodiscard]] int getCols() const;
  [[nodiscard]] const std::vector<std::vector<bool>> &getRightWalls() const;
  [[nodiscard]] const std::vector<std::vector<bool>> &getBottomWalls() const;

  void setRows(int rows);
  void setCols(int cols);
  void setRightWalls(const std::vector<std::vector<bool>> &rightWalls);
  void setBottomWalls(const std::vector<std::vector<bool>> &bottomWalls);

 private:
  std::vector<std::vector<bool>> rightWalls_;
  std::vector<std::vector<bool>> bottomWalls_;
  int rows_{};
  int cols_{};
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MAZE_MODELS_MAZE_H_
