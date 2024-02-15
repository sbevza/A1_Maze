#include "cave.h"

#include "ui_cave.h"

Cave::Cave(QWidget *parent)
    : QWidget(parent), ui(new Ui::Cave), controller(new CaveController) {
  ui->setupUi(this);
  ui->mil_step_text->setEnabled(false);
  ui->mil_step->setEnabled(false);

  stepTimer = new QTimer(this);

  connect(stepTimer, &QTimer::timeout, this, &Cave::on_timer_tick);
  connect(ui->mil_step, SIGNAL(valueChanged(int)), this,
          SLOT(on_mil_step_valueChanged(int)));
}

Cave::~Cave() {
  delete ui;
  delete stepTimer;
}

void Cave::on_timer_tick() { on_next_step_clicked(); }

void Cave::on_gen_mode_auto_clicked(bool checked) {
  ui->next_step->setEnabled(!checked);
  if (checked) {
    ui->mil_step_text->setEnabled(true);
    ui->mil_step->setEnabled(true);
    int mil_step = ui->mil_step->value();
    stepTimer->start(mil_step);
  }
}

void Cave::on_gen_mode_manual_clicked(bool checked) {
  ui->mil_step_text->setEnabled(!checked);
  ui->mil_step->setEnabled(!checked);
  if (checked) {
    ui->next_step->setEnabled(true);
    stepTimer->stop();
  }
}

void Cave::on_create_cave_clicked() {
  int sizeX = ui->size_cave_x->text().toInt();
  int sizeY = ui->size_cave_y->text().toInt();
  double initChance = ui->init_chance->text().toDouble() / 100.0;

  controller->createCave(sizeX, sizeY, initChance);
  auto cave = controller->getCave();

  QGraphicsScene *scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, 498, 498);
  double cellWidth = 500.0 / sizeX;
  double cellHeight = 500.0 / sizeY;

  for (int y = 0; y < sizeY; ++y) {
    for (int x = 0; x < sizeX; ++x) {
      scene->addRect(x * cellWidth, y * cellHeight, cellWidth, cellHeight,
                     Qt::NoPen, cave[y][x] ? Qt::black : Qt::white);
    }
  }

  ui->graphicsView->setScene(scene);
}

void Cave::on_file_clicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, tr("Открыть файл пещеры"), "", tr("Текстовые файлы (*.txt)"));
  if (filePath.isEmpty()) {
    return;
  }

  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox::warning(this, tr("Ошибка"),
                         tr("Не удалось открыть файл: %1").arg(filePath));
    return;
  }

  QTextStream in(&file);
  in >> sizeX >> sizeY;

  cave.resize(sizeY);
  for (int y = 0; y < sizeY; ++y) {
    cave[y].resize(sizeX);
    for (int x = 0; x < sizeX; ++x) {
      in >> cave[y][x];
    }
  }

  file.close();
  controller->setCave(cave);  // Обновляем состояние модели в контроллере

  drawCave(cave);
}

void Cave::on_next_step_clicked() {
  int limitDeath = ui->limit_death->text().toInt();
  int limitBirth = ui->limit_birth->text().toInt();
  controller->nextStep(limitDeath, limitBirth);
  auto updatedCave = controller->getCave();
  drawCave(updatedCave);
}

void Cave::drawCave(const std::vector<std::vector<int>> &cave) {
  auto currentScene = ui->graphicsView->scene();

  delete currentScene;

  int sizeY = cave.size();
  int sizeX = sizeY ? cave[0].size() : 0;

  auto *scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, 498, 498);

  double cellWidth = 500.0 / sizeX;
  double cellHeight = 500.0 / sizeY;

  for (int y = 0; y < sizeY; ++y) {
    for (int x = 0; x < sizeX; ++x) {
      scene->addRect(x * cellWidth, y * cellHeight, cellWidth, cellHeight,
                     Qt::NoPen, cave[y][x] ? Qt::black : Qt::white);
    }
  }

  ui->graphicsView->setScene(scene);
}

void Cave::on_mil_step_valueChanged(int value) {
  if (ui->gen_mode_auto->isChecked() && stepTimer->isActive()) {
    stepTimer->start(value);
  }
}
