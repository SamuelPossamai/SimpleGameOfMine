
#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>

#include "types.h"

class HelpWidget : public QWidget {

    Q_OBJECT

public:

    HelpWidget(MainWindow * = nullptr);

    void setParent(MainWindow *);
    void setParent(QWidget *) = delete;

private slots:

    void _return_button_pressed();
};

#endif // HELPWIDGET_H
