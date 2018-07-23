
#include <QApplication>

#include "mainwindow.h"
#include "menu.h"

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    MainWindow mw;

    mw.show();

    mw.pushWidget(new Menu);

    return app.exec();
}
