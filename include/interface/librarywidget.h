
#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include "mainwidget.h"

namespace Ui {
class LibraryWidget;
}

class LibraryWidget : public MainWidget {

    Q_OBJECT

public:

    explicit LibraryWidget(MainWindow *parent = 0);
    ~LibraryWidget();

private:

    Ui::LibraryWidget *_ui;
};

#endif // LIBRARYWIDGET_H
