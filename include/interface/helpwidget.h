
#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include "mainwidget.h"

namespace Ui {
class HelpWidget;
} /* namespace Ui */

class HelpWidget : public MainWidget {

    Q_OBJECT

public:

    explicit HelpWidget(MainWindow * = nullptr);
    virtual ~HelpWidget() override;

    virtual void activate() override;

private slots:

    void on_pushButton_clicked();

private:

    Ui::HelpWidget *_ui;
};

#endif // HELPWIDGET_H
