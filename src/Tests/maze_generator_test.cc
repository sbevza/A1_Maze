#include "../Maze/models/maze_generator.h"

#include <gtest/gtest.h>

#include <vector>

#include "../Maze/models/maze.h"

namespace s21 {

class MazeGeneratorTest : public ::testing::Test {
 protected:
  Maze maze;
  MazeGenerator *generator;

  void SetUp() override {
    // Инициализация мейза с заданными параметрами размеров
    maze.setRows(10);  // Пример размера
    maze.setCols(10);
    generator = new MazeGenerator(maze);
  }

  void TearDown() override { delete generator; }
};

TEST_F(MazeGeneratorTest, GeneratesMazeSuccessfully) {
  ASSERT_TRUE(generator->generate());
  ASSERT_EQ(maze.getRows(), 10);
  ASSERT_EQ(maze.getCols(), 10);
}

// Тест на проверку правильности генерации стен
TEST_F(MazeGeneratorTest, WallsGeneratedCorrectly) {
  generator->generate();
  auto rightWalls = maze.getRightWalls();
  auto bottomWalls = maze.getBottomWalls();
  // Пример проверки: убедиться, что крайние стены существуют
  for (int i = 0; i < maze.getRows(); ++i) {
    ASSERT_TRUE(rightWalls[i][maze.getCols() - 1]);
  }
  for (int j = 0; j < maze.getCols(); ++j) {
    ASSERT_TRUE(bottomWalls[maze.getRows() - 1][j]);
  }
  // Добавьте здесь дополнительные проверки стен
}

TEST_F(MazeGeneratorTest, GeneratesUniqueMazes) {
  generator->generate();
  auto firstMazeWalls =
      maze.getBottomWalls();  // Пример получения стен первого лабиринта

  generator->generate();
  auto secondMazeWalls = maze.getBottomWalls();  // Стены второго лабиринта

  // Сравниваем, что хотя бы одна стена отличается
  bool isDifferent = false;
  for (int i = 0; i < maze.getRows(); ++i) {
    for (int j = 0; j < maze.getCols(); ++j) {
      if (firstMazeWalls[i][j] != secondMazeWalls[i][j]) {
        isDifferent = true;
        break;
      }
    }
    if (isDifferent) break;
  }
  ASSERT_TRUE(isDifferent);
}

}  // namespace s21
