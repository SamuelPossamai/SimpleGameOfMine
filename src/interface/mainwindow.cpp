
#include <QKeyEvent>

#include "config/sgomfiles.h"
#include "mainwindow.h"
#include "mainwidget.h"
#include "interface_traits.h"

MainWindow::MainWindow() {

    setGeometry(Traits<MainWindow>::x, Traits<MainWindow>::y, Traits<MainWindow>::width, Traits<MainWindow>::height);
    if(SGOMFiles::get()->readSGOMConfigFile()["Game Start"]["fullscreen"] == "yes") this->showFullScreen();

    restoreProperties();
}

void MainWindow::pushWidget(MainWidget *w) {

    restoreProperties();

    w->setParent(this);
    w->setGeometry(0, 0, width(), height());

    if(_widgets.size() > 0) {

        _widgets.back()->hide();
        _widgets.back()->deactivate();
    }

    _widgets.push_back(w);

    w->activate();
    w->setFocus();
    w->show();
}

void MainWindow::popWidget() {

    restoreProperties();

    delete _widgets.back();
    _widgets.pop_back();

    _widgets.back()->setGeometry(0, 0, width(), height());

    if(!_widgets.empty()){

        _widgets.back()->setFocus();
        _widgets.back()->show();
        _widgets.back()->activate();
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {

    if(event->key() == Qt::Key_F12) {

        this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
    }
    if(event->key() == Qt::Key_F11) {

        this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
    }
}

void MainWindow::swapWidget(MainWidget *w) {

    restoreProperties();

    w->setParent(this);
    w->setGeometry(0, 0, width(), height());

    delete _widgets.back();

    w->activate();
    w->setFocus();
    (_widgets.back() = w)->show();
}

void MainWindow::resizeEvent(QResizeEvent* event) {

    if(!_widgets.empty()) _widgets.back()->resize(width(), height());
    QMainWindow::resizeEvent(event);
}

void MainWindow::restoreProperties() {

    setAutoFillBackground(true);
    setWindowTitle(Traits<MainWindow>::name);
    setStyleSheet("background-color: rgb(245, 245, 245);"
                  "color: rgb(20, 20, 20);");
}
