#ifndef A1_MAZE_1_SRC_MAZE_CONTROLLERS_CAVECONTROLLER_H
#define A1_MAZE_1_SRC_MAZE_CONTROLLERS_CAVECONTROLLER_H

#include <QObject>

#include "../models/cave_model.h"

class CaveController : public QObject {
  Q_OBJECT

 public:
  explicit CaveController(QObject *parent = nullptr);
  void createCave(int sizeX, int sizeY, double initChance);
  void nextStep(int limitDeath, int limitBirth);
  std::vector<std::vector<int>> getCave() const;
  void setCave(const std::vector<std::vector<int>> &newCave);

 signals:
  void caveUpdated(const std::vector<std::vector<int>> &cave);

 private:
  s21::CaveModel model_;
};

#endif  // A1_MAZE_1_SRC_MAZE_CONTROLLERS_CAVE_CONTROLLER_H
