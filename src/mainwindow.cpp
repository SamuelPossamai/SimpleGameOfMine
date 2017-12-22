
#include <QGraphicsScene>

#include "mainwindow.h"

MainWindow::MainWindow(){

    _gview = new QGraphicsView(new QGraphicsScene, this);

    setCentralWidget(_gview);
}
