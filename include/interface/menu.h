
#ifndef MENU_H
#define MENU_H

#include "types.h"
#include "mainwidget.h"

namespace Ui {
class Menu;
} /* namespace Ui */

class Menu : public MainWidget {

    Q_OBJECT

public:

    Menu(MainWindow *parent = nullptr);

    virtual ~Menu();

protected:

    virtual void activate() override;

private slots:

    void on_startButton_clicked();

    void on_helpButton_clicked();

    void on_testButton_clicked();

private:

    Ui::Menu *_ui;
};

#endif // MENU_H
