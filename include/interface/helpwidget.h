
#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include "mainwidget.h"

class HelpWidget : public MainWidget {

    Q_OBJECT

public:

    explicit HelpWidget(MainWindow * = nullptr);

private slots:

    void _return_button_pressed();
};

#endif // HELPWIDGET_H
