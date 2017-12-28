
#include "mainwindow.h"
#include "battlewidget.h"
#include "traits.h"

MainWindow::MainWindow() {

    setGeometry(Traits<MainWindow>::x, Traits<MainWindow>::y, Traits<MainWindow>::width, Traits<MainWindow>::height);

    setWindowTitle(Traits<MainWindow>::name);

    _b_scene = new BattleWidget(this);

    _b_scene->setGeometry(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height);
}
