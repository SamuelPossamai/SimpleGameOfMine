
#include <QApplication>
#include <QFile>

#include "mainwindow.h"
#include "menu.h"

int main(int argc, char **argv) {

    QApplication::setStyle("Fusion");

    QApplication app(argc, argv);

    QFile file(":/qss/stylesheet.qss");

    if(file.open(QFile::ReadOnly)) qApp->setStyleSheet(file.readAll());

    MainWindow mw;

    mw.show();

    mw.pushWidget(new Menu);

    return app.exec();
}
