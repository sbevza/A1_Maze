#include "mainwindow.h"

#include "cave.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(new s21::MazeController) {
  ui->setupUi(this);

  connect(controller_, &s21::MazeController::mazeLoaded, this,
          &MainWindow::onMazeLoaded);
  connect(controller_, &s21::MazeController::error, this, &MainWindow::onError);
  connect(controller_, &s21::MazeController::drawPath, this,
          &MainWindow::onDrawPath);

  //устанавливаем первоначальную рамку в 2px
  auto *scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, 498, 498);
  QPen pen(Qt::white, 2);
  scene->addRect(0, 0, 498, 498, pen);
  scene->setBackgroundBrush(Qt::black);
  ui->graphicsView->setScene(scene);

  setSolvedBlock(false);
}

MainWindow::~MainWindow() {
  delete ui;
  delete controller_;
}

void MainWindow::setSolvedBlock(bool enabled) {
  ui->end_point_text->setEnabled(enabled);
  ui->end_x->setEnabled(enabled);
  ui->end_y->setEnabled(enabled);
  ui->find_solving_maze->setEnabled(enabled);
  ui->start_point_text->setEnabled(enabled);
  ui->start_x->setEnabled(enabled);
  ui->start_y->setEnabled(enabled);
  ui->save_maze->setEnabled(enabled);
}

void MainWindow::on_cave_window_clicked() {
  if (!caveWindow_) {
    caveWindow_ = new Cave(this);
    caveWindow_->setWindowFlags(Qt::Window);
    caveWindow_->setAttribute(Qt::WA_DeleteOnClose);

    connect(caveWindow_, &QObject::destroyed, this, &MainWindow::onCaveClosed);
    ui->cave_window->setEnabled(false);
  }

  QPoint pos = this->pos();
  QSize size = this->size();

  int newX = pos.x() + size.width() + 5;
  int newY = pos.y();

  caveWindow_->setWindowFlags(Qt::Window);
  caveWindow_->move(newX, newY);
  caveWindow_->show();
}

void MainWindow::onCaveClosed() {
  caveWindow_ = nullptr;
  ui->cave_window->setEnabled(true);
}

void MainWindow::drawMaze(QGraphicsScene *scene, int rows, int cols,
                          const std::vector<std::vector<bool>> &rightWalls,
                          const std::vector<std::vector<bool>> &bottomWalls) {
  auto viewWidth = static_cast<qreal>(ui->graphicsView->width());
  auto viewHeight = static_cast<qreal>(ui->graphicsView->height());

  qreal cellWidth = viewWidth / cols;
  qreal cellHeight = viewHeight / rows;

  QPen pen(Qt::white, 2);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (rightWalls[i][j]) {
        qreal x = (j + 1) * cellWidth;
        qreal yTop = i * cellHeight;
        qreal yBottom = (i + 1) * cellHeight;
        scene->addLine(x, yTop, x, yBottom, pen);
      }

      if (bottomWalls[i][j]) {
        qreal xLeft = j * cellWidth;
        qreal xRight = (j + 1) * cellWidth;
        qreal y = (i + 1) * cellHeight;
        scene->addLine(xLeft, y, xRight, y, pen);
      }
    }
  }
}

void MainWindow::on_gen_maze_clicked() {
  controller_->generateMaze(ui->size_maze_y->value(), ui->size_maze_x->value());
}

void MainWindow::on_load_maze_clicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, tr("Открыть файл лабиринта"), "", tr("Текстовые файлы (*.txt)"));
  if (!filePath.isEmpty()) {
    controller_->loadMazeFromFile(filePath.toStdString());
  }
}

void MainWindow::on_find_solving_maze_clicked() {
  int startX = ui->start_x->value();
  int startY = ui->start_y->value();
  int endX = ui->end_x->value();
  int endY = ui->end_y->value();
  controller_->findPath(startX, startY, endX, endY);
}

void MainWindow::onMazeLoaded(

    int rows, int cols, const std::vector<std::vector<bool>> &rightWalls,
    const std::vector<std::vector<bool>> &bottomWalls) {
  mazeRows_ = rows;
  mazeCols_ = cols;

  auto *scene = new QGraphicsScene(this);
  scene->setSceneRect(0, 0, 498, 498);
  QPen pen(Qt::white, 2);
  scene->addRect(0, 0, 498, 498, pen);
  scene->setBackgroundBrush(Qt::black);

  drawMaze(scene, rows, cols, rightWalls, bottomWalls);

  setSolvedBlock(true);
  ui->start_y->setMaximum(rows);
  ui->start_x->setMaximum(cols);
  ui->end_y->setMaximum(rows);
  ui->end_x->setMaximum(cols);
  ui->end_y->setValue(rows);
  ui->end_x->setValue(cols);

  ui->graphicsView->setScene(scene);
}

void MainWindow::onError(const std::string &str) {
  QString message = QString::fromStdString(str);
  QMessageBox::critical(this, tr("Ошибка"), message);
}

void MainWindow::onDrawPath(const std::vector<s21::Point> &path) {
  static QGraphicsPathItem *currentPathItem = nullptr;

  if (currentPathItem != nullptr) {
    ui->graphicsView->scene()->removeItem(currentPathItem);
    delete currentPathItem;
    currentPathItem = nullptr;
  }

  float cellWidth = ui->graphicsView->width() / static_cast<float>(mazeCols_);
  float cellHeight = ui->graphicsView->height() / static_cast<float>(mazeRows_);

  QPainterPath painterPath;
  painterPath.moveTo(path.front().x * cellWidth + cellWidth / 2,
                     path.front().y * cellHeight + cellHeight / 2);

  currentPathItem = new QGraphicsPathItem();
  currentPathItem->setPen(QPen(Qt::red, 2));
  currentPathItem->setZValue(1.0);
  ui->graphicsView->scene()->addItem(currentPathItem);

  auto *animation = new QVariantAnimation(this);
  animation->setDuration(1000);
  animation->setStartValue(0);
  animation->setEndValue(static_cast<int>(path.size() - 1));

  QObject::connect(
      animation, &QVariantAnimation::valueChanged, this,
      [=](const QVariant &value) {
        int currentIndex = value.toInt();
        QPainterPath animatedPath;
        animatedPath.moveTo(path.front().x * cellWidth + cellWidth / 2,
                            path.front().y * cellHeight + cellHeight / 2);

        for (int i = 0; i <= currentIndex; ++i) {
          animatedPath.lineTo(path[i].x * cellWidth + cellWidth / 2,
                              path[i].y * cellHeight + cellHeight / 2);
        }

        currentPathItem->setPath(animatedPath);
      });

  animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::on_save_maze_clicked() {
  QString filePath = QFileDialog::getSaveFileName(
      this, tr("Сохранить лабиринт"), "", tr("Текстовые файлы (*.txt)"));
  if (!filePath.isEmpty()) {
    controller_->saveMazeToFile(filePath.toStdString());
  }
}
