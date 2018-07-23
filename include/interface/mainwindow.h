#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "types.h"

/*!
 * \brief Class used to manage the widgets that are displayed in the screen.
 * \brief Have a stack with all the widgets inside, the top is displayed.
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    /*!
     * \brief Creates a MainWindow object without any parameter.
     */
    MainWindow();

    /*!
     * \brief Push a widget to the widget's stack and display it.
     * \sa popWidget(), swapWidget(QWidget *)
     * \param w widget added to this object, it will be displayed in the screen.
     */
    void pushWidget(MainWidget *w);

    /*!
     * \brief Pop a widget from the widget's stack, the current widget will be destroyed and the previous one will be displayed.
     * \brief If there is no more widgets, it will display nothing.
     * \sa pushWidget(QWidget *), swapWidget(QWidget *)
     */
    void popWidget();

    /*!
     * \brief Swap the current widget beeing display, the current one will be destroyed.
     * \param w widget that will replace the current widget.
     * \sa pushWidget(QWidget *), popWidget()
     */
    void swapWidget(MainWidget *w);

private:

    std::vector<MainWidget *> _widgets;
};

#endif // MAINWINDOW_H
