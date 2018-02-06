
#include <QApplication>

#include "mainwindow.h"
#include "battlewidget.h"
#include "menu.h"

int main(int argc, char **argv) {

    QApplication app(argc, argv);

    MainWindow mw;

    mw.show();

    //mw.pushWidget(new BattleWidget);
    mw.pushWidget(new Menu);

    return app.exec();
}
