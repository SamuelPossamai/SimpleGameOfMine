#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include "types.h"
#include "animation.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    MainWindow();

public slots:

    void step();

private:

    QGraphicsView *_gview;
    QTimer *_timer;

    IntegerType _angle;

    Animation _animation;
};

#endif // MAINWINDOW_H
