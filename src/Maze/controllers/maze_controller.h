#ifndef A1_MAZE_1_SRC_MAZE_CONTROLLERS_MAZECONTROLLER_H_
#define A1_MAZE_1_SRC_MAZE_CONTROLLERS_MAZECONTROLLER_H_

#include <QObject>

#include "../models/maze.h"
#include "../models/maze_generator.h"
#include "../models/maze_solver.h"

namespace s21 {

class MazeController : public QObject {
  Q_OBJECT

 public:
  MazeController();
  ~MazeController() override;

  void loadMazeFromFile(const std::string &filePath);
  void saveMazeToFile(const std::string &filePath);
  [[nodiscard]] const Maze *getModel() const { return model_; }
  void findPath(int x1, int y1, int x2, int y2);
  void generateMaze(int rows, int cols);

  int getRows() const;
  int getCols() const;

 signals:
  void mazeLoaded(int rows, int cols,
                  const std::vector<std::vector<bool>> &rightWalls,
                  const std::vector<std::vector<bool>> &bottomWalls);
  void error(std::string str);
  void drawPath(std::vector<s21::Point> path);

 private:
  s21::Maze *model_;
  s21::MazeSolver *solver;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MAZE_CONTROLLERS_MAZECONTROLLER_H_
