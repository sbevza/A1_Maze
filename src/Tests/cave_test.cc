#include <gtest/gtest.h>

#include "../Maze/models/cave_model.h"

class TestCaveModel : public ::testing::Test {
 protected:
  void SetUp() override {
    int sizeX = 4;
    int sizeY = 4;
    double initChance = 0.5;
    model.generateCave(sizeX, sizeY, initChance);
  }

  s21::CaveModel model;
};

TEST_F(TestCaveModel, GenerateCaveTest) {
  int sizeX = 10;
  int sizeY = 10;
  double initChance = 0.5;
  model.generateCave(sizeX, sizeY, initChance);

  auto cave = model.getCave();
  ASSERT_EQ(cave.size(), sizeY);
  for (const auto& row : cave) {
    ASSERT_EQ(row.size(), sizeX);
  }
}

TEST_F(TestCaveModel, NextStepTest) {
  model.nextStep(2, 3);
  auto cave = model.getCave();
  ASSERT_EQ(cave.size(), 4);  // Проверка количества строк
  for (const auto& row : cave) {
    ASSERT_EQ(row.size(), 4);  // Проверка размера каждой строки
  }
}

TEST_F(TestCaveModel, SetAndGetCave) {
  std::vector<std::vector<int>> expectedCave = {
      {0, 1, 0, 1}, {1, 0, 0, 1}, {0, 1, 0, 0}, {0, 0, 1, 1}};
  model.setCave(expectedCave);
  auto actualCave = model.getCave();
  ASSERT_EQ(expectedCave, actualCave);
}