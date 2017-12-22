#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    MainWindow();

private:

    QGraphicsView *_gview;
};

#endif // MAINWINDOW_H
