#ifndef A1_MAZE_1_SRC_MAZE_MAINWINDOW_H_
#define A1_MAZE_1_SRC_MAZE_MAINWINDOW_H_

#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QVariantAnimation>
#include <vector>

#include "../controllers/maze_controller.h"
#include "cave.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

 private slots:
  void setSolvedBlock(bool enabled);
  void on_cave_window_clicked();
  void onCaveClosed();
  void on_gen_maze_clicked();
  void on_load_maze_clicked();
  void on_find_solving_maze_clicked();
  void onMazeLoaded(int rows, int cols,
                    const std::vector<std::vector<bool>> &rightWalls,
                    const std::vector<std::vector<bool>> &bottomWalls);
  void onError(const std::string &str);
  void on_save_maze_clicked();

 private:
  Ui::MainWindow *ui;
  Cave *caveWindow_ = nullptr;
  s21::MazeController *controller_;

  int mazeRows_{};
  int mazeCols_{};

  void onDrawPath(const std::vector<s21::Point> &path);
  void drawMaze(QGraphicsScene *scene, int rows, int cols,
                const std::vector<std::vector<bool>> &rightWalls,
                const std::vector<std::vector<bool>> &bottomWalls);
};

#endif  // A1_MAZE_1_SRC_MAZE_MAINWINDOW_H_
