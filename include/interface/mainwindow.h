#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "types.h"

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    MainWindow();

    void pushWidget(QWidget *w);
    void popWidget();
    void switchWidget(QWidget *w);

private:

    std::vector<QWidget *> _widgets;
};

#endif // MAINWINDOW_H
