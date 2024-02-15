#ifndef A1_MAZE_1_SRC_MAZE_MODELS_CAVEMODEL_H_
#define A1_MAZE_1_SRC_MAZE_MODELS_CAVEMODEL_H_

#include <cstddef>
#include <random>
#include <vector>

namespace s21 {

class CaveModel {
 public:
  CaveModel();
  void generateCave(int sizeX, int sizeY, double initChance);
  void nextStep(int limitDeath, int limitBirth);
  std::vector<std::vector<int>> getCave() const;
  void setCave(const std::vector<std::vector<int>> &newCave);

 private:
  std::vector<std::vector<int>> cave;
  int countAliveNeighbors(int x, int y) const;
};

}  // namespace s21

#endif  // A1_MAZE_1_SRC_MAZE_MODELS_CAVEMODEL_H_
