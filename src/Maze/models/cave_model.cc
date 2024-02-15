#include "cave_model.h"

namespace s21 {

CaveModel::CaveModel() {}

void CaveModel::generateCave(int sizeX, int sizeY, double initChance) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::bernoulli_distribution d(initChance);

  cave.resize(sizeY);
  for (int y = 0; y < sizeY; ++y) {
    cave[y].resize(sizeX);
    for (int x = 0; x < sizeX; ++x) {
      cave[y][x] = d(gen) ? 1 : 0;
    }
  }
}

void CaveModel::nextStep(int limitDeath, int limitBirth) {
  std::vector<std::vector<int>> nextCave = cave;

  for (std::size_t y = 0; y < cave.size(); ++y) {
    for (std::size_t x = 0; x < cave[y].size(); ++x) {
      int aliveNeighbors = countAliveNeighbors(x, y);

      if (cave[y][x] == 1 && aliveNeighbors < limitDeath) {
        nextCave[y][x] = 0;
      } else if (cave[y][x] == 0 && aliveNeighbors >= limitBirth) {
        nextCave[y][x] = 1;
      }
    }
  }

  cave = nextCave;
}

int CaveModel::countAliveNeighbors(int x, int y) const {
  int count = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0) continue;

      int nx = x + j;
      int ny = y + i;
      if (nx >= 0 && static_cast<std::size_t>(nx) < cave[0].size() && ny >= 0 &&
          static_cast<std::size_t>(ny) < cave.size()) {
        count += cave[ny][nx];
      }
    }
  }
  return count;
}

std::vector<std::vector<int>> CaveModel::getCave() const { return cave; }

void CaveModel::setCave(const std::vector<std::vector<int>> &newCave) {
  cave = newCave;
}

}  // namespace s21