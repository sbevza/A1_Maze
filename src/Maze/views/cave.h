#ifndef CAVE_H
#define CAVE_H

#include <QFile>
#include <QFileDialog>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QTimer>
#include <QWidget>

#include "../controllers/cave_controller.h"

namespace Ui {
class Cave;
}

class Cave : public QWidget {
  Q_OBJECT

 public:
  explicit Cave(QWidget *parent = nullptr);
  ~Cave() override;

 private slots:
  void on_gen_mode_auto_clicked(bool checked);

  void on_gen_mode_manual_clicked(bool checked);

  void on_create_cave_clicked();

  void on_file_clicked();

  void on_next_step_clicked();

  void drawCave(const std::vector<std::vector<int>> &cave);

  void on_mil_step_valueChanged(int value);

 private:
  Ui::Cave *ui;

  CaveController *controller;

  QTimer *stepTimer;

  std::vector<std::vector<int>> cave;  // Измените тип данных здесь
  int sizeX{};
  int sizeY{};

  void on_timer_tick();
};

#endif  // CAVE_H
