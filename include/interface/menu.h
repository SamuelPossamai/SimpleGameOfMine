#ifndef MENU_H
#define MENU_H

#include <QWidget>

#include "types.h"

class Menu : public QWidget {

public:

    Menu(MainWindow *parent = nullptr);

    void setParent(MainWindow *);
    void setParent(QWidget *) = delete;

private slots:

    void _start_button_clicked();

private:

};

#endif // MENU_H
