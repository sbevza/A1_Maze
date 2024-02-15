#include "maze_generator.h"

namespace s21 {

MazeGenerator::MazeGenerator(Maze &maze)
    : maze_(maze), rows_(maze_.getRows()), cols_(maze_.getCols()) {}

bool MazeGenerator::generate() {
  matrix_.resize(rows_, std::vector<Cell>(cols_));

  for (int currentRow = 0; currentRow < rows_; ++currentRow) {
    joinCellsToUniqueSets(currentRow);
    createRightWalls(currentRow);
    createBottomWalls(currentRow);

    if (currentRow < rows_ - 1) {
      prepareNextRow(currentRow);
    } else {
      completeMaze(currentRow);
    }
  }

  transferMaze();
  return !matrix_.empty();
}

void MazeGenerator::transferMaze() {
  std::vector<std::vector<bool>> rightWalls(rows_,
                                            std::vector<bool>(cols_, true));
  std::vector<std::vector<bool>> bottomWalls(rows_,
                                             std::vector<bool>(cols_, true));

  for (int y = 0; y < rows_; ++y) {
    for (int x = 0; x < cols_; ++x) {
      if (x < cols_ - 1) {
        rightWalls[y][x] = matrix_[y][x].rightWall;
      }
      if (y < rows_ - 1) {
        bottomWalls[y][x] = matrix_[y][x].bottomWall;
      }
    }
  }

  for (int y = 0; y < rows_; ++y) {
    rightWalls[y][cols_ - 1] = true;
  }
  for (int x = 0; x < cols_; ++x) {
    bottomWalls[rows_ - 1][x] = true;
  }

  maze_.setRightWalls(rightWalls);
  maze_.setBottomWalls(bottomWalls);
}

void MazeGenerator::joinCellsToUniqueSets(int currentRow) {
  for (int x = 0; x < cols_; ++x) {
    if (matrix_[currentRow][x].setId == -1) {
      matrix_[currentRow][x].setId = counterId_++;
    }
  }
}

void MazeGenerator::createRightWalls(int currentRow) {
  std::uniform_int_distribution<> dis(0, 1);

  for (int x = 0; x < cols_ - 1; ++x) {
    bool shouldAddWall = dis(gen_);

    if (shouldAddWall ||
        (matrix_[currentRow][x].setId == matrix_[currentRow][x + 1].setId)) {
      matrix_[currentRow][x].rightWall = true;
    } else {
      int targetSetId = matrix_[currentRow][x + 1].setId;
      for (int k = 0; k < cols_; ++k) {
        if (matrix_[currentRow][k].setId == targetSetId) {
          matrix_[currentRow][k].setId = matrix_[currentRow][x].setId;
        }
      }
    }
  }
}

void MazeGenerator::createBottomWalls(int currentRow) {
  std::uniform_int_distribution<> dis(0, 1);

  for (int x = 0; x < cols_; ++x) {
    bool shouldAddWall = dis(gen_);
    if (shouldAddWall) {
      int count{};
      int id = matrix_[currentRow][x].setId;
      for (int k = 0; k < cols_ && count <= 1; k++) {
        if (matrix_[currentRow][k].setId == id &&
            !matrix_[currentRow][k].bottomWall)
          count++;
      }
      if (count > 1) matrix_[currentRow][x].bottomWall = true;
    }
  }
}

void MazeGenerator::prepareNextRow(int currentRow) {
  for (int x = 0; x < cols_; ++x) {
    if (!matrix_[currentRow][x].bottomWall) {
      matrix_[currentRow + 1][x].setId = matrix_[currentRow][x].setId;
    }
  }

  for (int x = 0; x < cols_ - 1; ++x) {
    matrix_[currentRow + 1][x].rightWall = false;
  }

  for (int x = 0; x < cols_; ++x) {
    if (matrix_[currentRow][x].bottomWall) {
      matrix_[currentRow + 1][x].setId = -1;
    }
    matrix_[currentRow + 1][x].bottomWall = false;
  }
}

void MazeGenerator::completeMaze(int currentRow) {
  for (int x = 0; x < cols_; ++x) {
    matrix_[currentRow][x].bottomWall = true;
  }

  int universalSetId = matrix_[currentRow][0].setId;

  for (int x = 0; x < cols_ - 1; ++x) {
    if (matrix_[currentRow][x].setId != matrix_[currentRow][x + 1].setId) {
      matrix_[currentRow][x].rightWall = false;
      int targetSetId = matrix_[currentRow][x + 1].setId;

      for (int k = 0; k < cols_; ++k) {
        if (matrix_[currentRow][k].setId == targetSetId) {
          matrix_[currentRow][k].setId = universalSetId;
        }
      }
    }
  }
}

}  // namespace s21
