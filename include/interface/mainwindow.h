
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "types.h"

/*!
 * \brief Class used to manage the widgets that are displayed in the screen.
 * \brief Have a stack with all the widgets inside, the top is displayed.
 * \sa MainWidget
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
     * \sa popWidget(), swapWidget(MainWidget *)
     * \param w widget added to this object, it will be displayed in the screen.
     */
    void pushWidget(MainWidget *w);

    /*!
     * \brief Pop a widget from the widget's stack, the current widget will be destroyed and the previous one will be displayed.
     * \brief If there is no more widgets, it will display nothing.
     * \sa pushWidget(MainWidget *), swapWidget(MainWidget *)
     */
    void popWidget();

    /*!
     * \brief Swap the current widget beeing display, the current one will be destroyed.
     * \param w widget that will replace the current widget.
     * \sa pushWidget(MainWidget *), popWidget()
     */
    void swapWidget(MainWidget *w);

protected:

    void keyPressEvent(QKeyEvent* event) final;

    void restoreProperties();
    void resizeEvent(QResizeEvent* event) final;

private:

    void _change_window_apply(MainWidget *w);

    std::vector<MainWidget *> _widgets;
};

#endif // MAINWINDOW_H
