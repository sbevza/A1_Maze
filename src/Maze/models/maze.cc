#include "maze.h"

namespace s21 {

bool Maze::loadFromFile(const std::string &filePath) {
  bool success = true;
  std::ifstream file(filePath);

  if (!file.is_open()) {
    std::cerr << "Не удалось открыть файл: " << filePath << std::endl;
    success = false;
  } else {
    file >> rows_ >> cols_;

    rightWalls_.resize(rows_, std::vector<bool>(cols_, false));
    bottomWalls_.resize(rows_, std::vector<bool>(cols_, false));

    for (int i = 0; i < rows_ && success; ++i) {
      for (int j = 0; j < cols_ && success; ++j) {
        int wall;
        if (!(file >> wall)) {
          success = false;
        }
        rightWalls_[i][j] = wall;
      }
    }

    for (int i = 0; i < rows_ && success; ++i) {
      for (int j = 0; j < cols_ && success; ++j) {
        int wall;
        if (!(file >> wall)) {
          success = false;
        }
        bottomWalls_[i][j] = wall;
      }
    }

    if (file.fail() && success) {
      std::cerr << "Ошибка при чтении файла: " << filePath << std::endl;
      success = false;
    }
  }

  return success;
}

bool Maze::saveToFile(const std::string &filePath) {
  bool success = true;
  std::ofstream file(filePath);

  if (!file.is_open()) {
    std::cerr << "Не удалось открыть файл для записи: " << filePath
              << std::endl;
    success = false;
  } else {
    file << rows_ << " " << cols_ << std::endl;

    for (int i = 0; i < rows_ && success; ++i) {
      for (int j = 0; j < cols_; ++j) {
        file << (rightWalls_[i][j] ? 1 : 0);
        if (j < cols_ - 1) file << " ";
      }
      file << std::endl;
    }

    file << std::endl;

    for (int i = 0; i < rows_ && success; ++i) {
      for (int j = 0; j < cols_; ++j) {
        file << (bottomWalls_[i][j] ? 1 : 0);
        if (j < cols_ - 1) file << " ";
      }
      if (i < rows_ - 1) file << std::endl;
    }

    if (file.fail()) {
      std::cerr << "Ошибка при записи в файл: " << filePath << std::endl;
      success = false;
    }
  }

  return success;
}

int Maze::getRows() const { return rows_; }
int Maze::getCols() const { return cols_; }

[[nodiscard]] const std::vector<std::vector<bool>> &Maze::getRightWalls()
    const {
  return rightWalls_;
}

[[nodiscard]] const std::vector<std::vector<bool>> &Maze::getBottomWalls()
    const {
  return bottomWalls_;
}

void Maze::setRows(int rows) { rows_ = rows; }
void Maze::setCols(int cols) { cols_ = cols; }
void Maze::setRightWalls(const std::vector<std::vector<bool>> &rightWalls) {
  rightWalls_ = rightWalls;
}
void Maze::setBottomWalls(const std::vector<std::vector<bool>> &bottomWalls) {
  bottomWalls_ = bottomWalls;
}

}  // namespace s21