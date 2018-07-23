
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <config/types.h>

#include "mainwindow.h"

class MainWidget : public QWidget {

public:

    explicit MainWidget(MainWindow *parent = nullptr) : QWidget(parent) {}

    virtual ~MainWidget() {}

    void setParent(MainWindow *p) { QWidget::setParent(p); }
    void setParent(QWidget *) = delete;

    MainWindow *parent() { return static_cast<MainWindow *>(QWidget::parent()); }

    virtual void activate() {}
    virtual void deactivate() {}
};

#endif // MAINWIDGET_H
