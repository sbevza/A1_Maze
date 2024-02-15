#include "../Maze/models/maze_solver.h"

#include <gtest/gtest.h>

#include "../Maze/models/maze.h"  // Предполагаем, что у вас есть такой файл

namespace s21 {

s21::Maze CreateTestMaze(int rows, int cols,
                         const std::vector<std::vector<bool>> &rightWalls,
                         const std::vector<std::vector<bool>> &bottomWalls) {
  s21::Maze maze;
  maze.setRows(rows);
  maze.setCols(cols);
  maze.setRightWalls(rightWalls);
  maze.setBottomWalls(bottomWalls);
  return maze;
}

TEST(MazeSolverTest, FindsPathThroughComplexMaze) {
  std::vector<std::vector<bool>> rightWalls = {
      {0, 0, 1, 0, 0, 0, 0, 1, 0, 1}, {0, 1, 1, 1, 0, 0, 0, 1, 1, 1},
      {1, 0, 1, 0, 0, 1, 1, 1, 1, 1}, {1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
      {0, 0, 1, 0, 1, 0, 1, 0, 1, 1}, {1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
      {0, 0, 0, 1, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
      {1, 0, 0, 0, 1, 1, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 1, 0, 0, 0, 1}};

  std::vector<std::vector<bool>> bottomWalls = {
      {0, 1, 0, 0, 0, 1, 1, 1, 0, 0}, {1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
      {0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 0, 1, 0, 0, 1, 0},
      {1, 0, 1, 1, 1, 0, 1, 1, 1, 0}, {0, 1, 1, 1, 0, 1, 0, 0, 0, 0},
      {1, 1, 0, 1, 0, 0, 1, 0, 1, 1}, {0, 1, 1, 1, 1, 0, 0, 0, 1, 0},
      {1, 0, 1, 0, 0, 0, 0, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}};

  s21::Maze maze;
  maze.setRightWalls(rightWalls);
  maze.setBottomWalls(bottomWalls);

  s21::MazeSolver solver(maze);
  auto path = solver.findPath(1, 1, 10, 10);

  ASSERT_FALSE(path.empty());
  ASSERT_EQ(path.front(), (s21::Point{0, 0}));
  ASSERT_EQ(path.back(), (s21::Point{9, 9}));
}

TEST(MazeSolverTest, FindsPathInAnotherComplexMaze) {
  std::vector<std::vector<bool>> rightWalls = {
      {1, 1, 0, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
      {1, 0, 0, 1, 0, 1, 1, 0, 1, 1}, {1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
      {0, 1, 0, 1, 0, 0, 1, 0, 1, 1}, {1, 0, 1, 0, 1, 0, 0, 1, 1, 1},
      {1, 0, 1, 1, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
      {1, 1, 0, 0, 1, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 0, 0, 0, 0, 0, 1}};

  std::vector<std::vector<bool>> bottomWalls = {
      {0, 0, 0, 1, 0, 1, 0, 0, 1, 0}, {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 1, 0, 0}, {0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 1, 1, 0, 0, 0}, {0, 1, 1, 0, 1, 0, 1, 1, 1, 0},
      {1, 1, 0, 0, 0, 1, 1, 0, 0, 1}, {0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
      {0, 0, 1, 1, 0, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}};

  s21::Maze maze;
  maze.setRightWalls(rightWalls);
  maze.setBottomWalls(bottomWalls);

  s21::MazeSolver solver(maze);
  auto path = solver.findPath(1, 1, 10, 10);

  // Проверяем, что путь найден
  ASSERT_FALSE(path.empty());
  ASSERT_EQ(path.front(),
            (s21::Point{0, 0}));  // Проверяем начальную точку пути
  ASSERT_EQ(path.back(), (s21::Point{9, 9}));  // Проверяем конечную точку пути
}

TEST(MazeSolverTest, PathNotFound) {
  s21::Maze maze =
      CreateTestMaze(3, 3, {{true, true}, {true, true}, {true, true}},
                     {{true, true}, {true, true}, {true, true}});
  s21::MazeSolver solver(maze);
  auto path = solver.findPath(1, 1, 3, 3);
  ASSERT_TRUE(path.empty());
}

}  // namespace s21
