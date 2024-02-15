#include "cave_controller.h"

CaveController::CaveController(QObject *parent) : QObject(parent) {}

void CaveController::createCave(int sizeX, int sizeY, double initChance) {
  model_.generateCave(sizeX, sizeY, initChance);
  emit caveUpdated(model_.getCave());
}

void CaveController::nextStep(int limitDeath, int limitBirth) {
  model_.nextStep(limitDeath, limitBirth);
  emit caveUpdated(model_.getCave());
}

std::vector<std::vector<int>> CaveController::getCave() const {
  return model_.getCave();
}

void CaveController::setCave(const std::vector<std::vector<int>> &newCave) {
  model_.setCave(newCave);
  emit caveUpdated(newCave);
}