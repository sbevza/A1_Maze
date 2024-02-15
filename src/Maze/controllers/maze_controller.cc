#include "maze_controller.h"

namespace s21 {

MazeController::MazeController() : model_(new Maze()) {
  solver = new MazeSolver(*model_);
}

MazeController::~MazeController() {
  delete model_;
  delete solver;
}

void MazeController::loadMazeFromFile(const std::string &filePath) {
  if (model_->loadFromFile(filePath)) {
    emit mazeLoaded(model_->getRows(), model_->getCols(),
                    model_->getRightWalls(), model_->getBottomWalls());
  } else {
    emit error("Ошибка открытия файла.");
  }
}

void MazeController::saveMazeToFile(const std::string &filePath) {
  model_->saveToFile(filePath);
}

void MazeController::findPath(int x1, int y1, int x2, int y2) {
  std::vector<s21::Point> path = solver->findPath(x1, y1, x2, y2);
  emit drawPath(path);
}

void MazeController::generateMaze(int rows, int cols) {
  model_->setRows(rows);
  model_->setCols(cols);
  MazeGenerator generator(*model_);
  if (generator.generate()) {
    emit mazeLoaded(rows, cols, model_->getRightWalls(),
                    model_->getBottomWalls());
  } else {
    emit error("Ошибка генерации лабиринта.");
  }
}

}  // namespace s21