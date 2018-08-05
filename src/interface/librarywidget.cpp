
#include "librarywidget.h"
#include "ui_librarywidget.h"

LibraryWidget::LibraryWidget(MainWindow *parent) : MainWidget(parent), _ui(new Ui::LibraryWidget) {

    _ui->setupUi(this);

    _ui->tabWidget->setCurrentIndex(0);
    _ui->jobTabWidget->setCurrentIndex(0);
    _ui->creatureTabWidget->setCurrentIndex(0);
}

LibraryWidget::~LibraryWidget() {

    delete _ui;
}

void LibraryWidget::on_returnButton_clicked() {

    parent()->popWidget();
}
