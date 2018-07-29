
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <config/types.h>

#include "mainwindow.h"

/*!
 * \brief Widget to be used along side with MainWindow, it can be pushed to the MainWindow stack
 * \sa MainWindow
 */
class MainWidget : public QWidget {

    Q_OBJECT

public:

    /*!
     * \brief Construct a MainWidget
     * \param parent Parent of this widget, should be an MainWindow or derived
     */
    explicit MainWidget(MainWindow *parent = nullptr) : QWidget(parent) {}

    virtual ~MainWidget() {}

    /*!
     * \brief Virtual method called when this widget become the top of the MainWindow's stack
     */
    virtual void activate() {}

    /*!
     * \brief Virtual method called when this widget stop being the top of the MainWindow's stack
     */
    virtual void deactivate() {}

    void setParent(MainWindow *p) { QWidget::setParent(p); }
    void setParent(QWidget *) = delete;

    MainWindow *parent() { return static_cast<MainWindow *>(QWidget::parent()); }
};

#endif // MAINWIDGET_H
