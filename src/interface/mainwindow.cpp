
#include <QWidget>

#include "mainwindow.h"
#include "interface_traits.h"

MainWindow::MainWindow() {

    setGeometry(Traits<MainWindow>::x, Traits<MainWindow>::y, Traits<MainWindow>::width, Traits<MainWindow>::height);

    setWindowTitle(Traits<MainWindow>::name);
}

void MainWindow::pushWidget(QWidget *w) {

    w->setParent(this);
    w->setGeometry(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height);

    if(_widgets.size() > 0) _widgets.back()->hide();
    _widgets.push_back(w);

    w->setFocus();
    w->show();
}

void MainWindow::popWidget() {

    delete _widgets.back();
    _widgets.pop_back();

    _widgets.back()->setFocus();
    _widgets.back()->show();
}

void MainWindow::switchWidget(QWidget *w) {

    w->setParent(this);
    w->setGeometry(0, 0, Traits<MainWindow>::width, Traits<MainWindow>::height);

    delete _widgets.back();

    w->setFocus();
    (_widgets.back() = w)->show();
}
