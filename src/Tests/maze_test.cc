#include "../Maze/models/maze.h"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

namespace s21 {

class MazeTest : public ::testing::Test {
 protected:
  Maze maze;

  void TearDown() override { std::filesystem::remove("test_maze_save.txt"); }
};

// Тест на проверку загрузки из файла Maze1.txt
TEST_F(MazeTest, LoadFromFileMaze1) {
  ASSERT_TRUE(maze.loadFromFile("Exemples/Maze1.txt"));
  ASSERT_TRUE(maze.saveToFile("test_maze_save.txt"));
}

// Тест на проверку загрузки из файла Maze2.txt
TEST_F(MazeTest, LoadFromFileMaze2) {
  ASSERT_TRUE(maze.loadFromFile("Exemples/Maze2.txt"));
  ASSERT_TRUE(maze.saveToFile("test_maze_save.txt"));
}

// Тест на проверку загрузки из файла Maze3.txt
TEST_F(MazeTest, LoadFromFileMaze3) {
  ASSERT_TRUE(maze.loadFromFile("Exemples/Maze3.txt"));
  ASSERT_TRUE(maze.saveToFile("test_maze_save.txt"));
}

TEST_F(MazeTest, FailsToLoadFromNonexistentFile) {
  ASSERT_FALSE(maze.loadFromFile("nonexistent_file.txt"));
}

TEST_F(MazeTest, SetAndGetRows) {
  maze.setRows(15);
  ASSERT_EQ(maze.getRows(), 15);
}

TEST_F(MazeTest, SetAndGetCols) {
  maze.setCols(20);
  ASSERT_EQ(maze.getCols(), 20);
}

TEST_F(MazeTest, SetAndGetRightWalls) {
  std::vector<std::vector<bool>> rightWalls(10, std::vector<bool>(10, true));
  maze.setRightWalls(rightWalls);
  ASSERT_EQ(maze.getRightWalls(), rightWalls);
}

TEST_F(MazeTest, SetAndGetBottomWalls) {
  std::vector<std::vector<bool>> bottomWalls(10, std::vector<bool>(10, false));
  maze.setBottomWalls(bottomWalls);
  ASSERT_EQ(maze.getBottomWalls(), bottomWalls);
}

TEST_F(MazeTest, HandlesIncorrectDataOnLoad) {
  std::string filePath = "incorrect_data_maze.txt";
  std::ofstream out(filePath);
  out << "5 5\n1 1\n";  // Намеренно некорректные данные
  out.close();

  ASSERT_FALSE(maze.loadFromFile(filePath));
  std::remove(filePath.c_str());
}

TEST_F(MazeTest, HandlesWriteErrorToFile) {
  std::string filePath = "/unwritable_directory/unwritable_file.txt";
  // Предполагается, что запись в этот путь невозможна
  ASSERT_FALSE(maze.saveToFile(filePath));
}

}  // namespace s21
