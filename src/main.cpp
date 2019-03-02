
#include <iostream>

#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QDir>
#include <QDirIterator>

#include "config/game_traits.h"

#include "mainwindow.h"
#include "menu.h"

int main(int argc, char **argv) {

    QApplication::setStyle("Fusion");

    QApplication app(argc, argv);
    QApplication::setApplicationName(Traits<Game>::name);
    QApplication::setApplicationVersion(Traits<Game>::version);

    QCommandLineParser parser;
    parser.setApplicationDescription(Traits<Game>::description);
    parser.addHelpOption();
    parser.addVersionOption();

    parser.process(app);

    {

        QString qss_content;

        QDir dir(":/qss");

        dir.setSorting(QDir::Name);

        for(auto filename: dir.entryList()) {

            QFileInfo fileinfo(dir, filename);

            if(!fileinfo.isFile() || fileinfo.suffix() != "qss") continue;

            QFile file(fileinfo.filePath());

            if(file.open(QFile::ReadOnly)) qss_content += file.readAll();
        }

        qApp->setStyleSheet(qss_content);
    }

    MainWindow mw;

    mw.show();

    mw.pushWidget(new Menu);

    return app.exec();
}
