
#include "ui_helpwidget.h"
#include "helpwidget.h"

HelpWidget::HelpWidget(MainWindow *w) : MainWidget(w), _ui(new Ui::HelpWidget) {

    _ui->setupUi(this);
}

HelpWidget::~HelpWidget() {

    delete _ui;
}

void HelpWidget::activate() {

    _ui->toolBox->setCurrentIndex(0);
}

void HelpWidget::on_pushButton_clicked() {

    parent()->popWidget();
}
