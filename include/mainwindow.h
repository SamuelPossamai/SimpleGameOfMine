#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "types.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    MainWindow();

private:

    BattleWidget *_b_scene;
};

#endif // MAINWINDOW_H
