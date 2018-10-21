
#ifndef MENU_H
#define MENU_H

#include "types.h"
#include "mainwidget.h"

namespace Ui {
class Menu;
} /* namespace Ui */

/*!
 * \brief Class that represents the interface for the game menu
 */
class Menu : public MainWidget {

    Q_OBJECT

public:

    /*!
     * \brief Create an menu
     * \param parent Parent of this widget, by default nullptr
     */
    Menu(MainWindow *parent = nullptr);

    virtual ~Menu();

protected:

    virtual void activate() override;

private slots:

    void on_startButton_clicked();

    void on_helpButton_clicked();

    void on_libraryButton_clicked();

    void on_configButton_clicked();

private:

    Ui::Menu *_ui;
};

#endif // MENU_H
